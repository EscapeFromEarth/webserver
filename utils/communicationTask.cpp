#include "utils/communicationTask.h"
#include "arpa/inet.h"
#include "cstring"
#include "dirent.h"
#include "fcntl.h"
#include "pthread.h"
#include "server.h"
#include "sys/epoll.h"
#include "sys/sendfile.h"
#include "sys/stat.h"
using namespace abcpony::utility;

CommunicationTask::CommunicationTask(int *cfd) : Task(cfd) {
}

void CommunicationTask::execute() {
	log_debug("communication task run");
	char buf[4096] = {}, tmp[1024] = {};
	int len = 0, tot = 0;
	const int cfd = *static_cast<int *>(arg);
	while ((len = recv(cfd, tmp, sizeof(tmp), 0)) > 0) {
		if (tot + len < sizeof(buf)) { // 如果超出 buf 的长度则不再接收 (解释: 请求行才是最主要的部分,
									   // 这个地方基本上保证了接收到请求行了, 后面的其他信息太多接收不了就算了)
			memcpy(buf + tot, tmp, sizeof(tmp));
		}
		tot += len; // 放这里就行，就是一次超了后面我也都不要了（反正后面不用到 tot）。
	}
	if (len == -1) {
		if (errno == EAGAIN) {
			// 本次接收完了  解析请求行 (这里只针对 GET)
			// 其实个人感觉这里还是有可能没接收完的，不过也不确定，可能客户端一条消息还没发完的概率很小吧。。或者有特殊的处理机制？
			char *pt = strstr(buf, "\r\n"); // strstr(a, b)：在 a 里面找到子串 b 第一次出现的位置。
			int reqLen = pt - buf;
			buf[reqLen] = '\0'; // 直接“*pt = 0”不香？
			parseRequestLine(buf, cfd);
		} else {
			log_error("recv error");
			return;
		}
	} else {
		log_debug("connection is closed by the client");
		// 客户端断开连接
		auto server = Singleton<Server>::instance();
		pthread_mutex_lock(&server->m_epfd_lock);
		epoll_ctl(server->m_epfd, EPOLL_CTL_DEL, cfd, NULL);
		pthread_mutex_unlock(&server->m_epfd_lock);
		close(cfd);
	}
}

void CommunicationTask::destroy() {
	log_debug("communication task destroy");
	delete static_cast<int *>(arg);
	arg = nullptr;
}

bool CommunicationTask::parseRequestLine(const char *line, int cfd) {
	char method[12], path[1024];
	sscanf(line, "%[^ ] %[^ ]", method, path);
	log_debug("method=%s path=%s\n", method, path);
	if (strcasecmp(method, "get") != 0) { // 忽略大小写的比较（<0则s1<s2，=0则s1=s2，>0则s1>s2）
		return false;
	}
	decodeMsg(path, path); // 因为解析只会更短，我保证了它这样传参能够正常解析。
	// 处理客户端请求的静态资源（文件/目录）
	char *file = NULL;
	if (strcmp(path, "/") == 0) {
		file = "./";
	} else {
		file = path + 1; // 去掉最前面的“/”即可
	}
	log_debug("file: %s\n", file);
	// 获取文件属性
	struct stat st;
	int ret = stat(file, &st);
	if (ret == -1) {
		// 文件不存在——回复404
		sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), -1); // 只是要返回 404，一定是 html 类型。
		sendFile("404.html", cfd);
		return true;
	}
	// 判断文件类型
	if (S_ISDIR(st.st_mode)) { // 目录
		log_debug("send dir");
		sendHeadMsg(cfd, 200, "OK", getFileType(".html"), -1);
		sendDir(file, cfd);
	} else { // 文件
		log_debug("send file");
		sendHeadMsg(cfd, 200, "OK", getFileType(file), st.st_size);
		sendFile(file, cfd);
	}

	return true;
}

bool CommunicationTask::sendFile(const char *filename, int cfd) { // 边读边发送
	// 打开文件
	log_debug("send file, filename=%s\n", filename);
	int fd = open(filename, O_RDONLY);
	assert(fd > 0);
#if 0 // 这里的条件设置为 0 就是下面的不执行（就看看），执行 else 部分
	while (1) {
		char buf[1024] = {};
		int len = read(fd, buf, sizeof(buf));
		if (len > 0) {
			send(cfd, buf, len, 0);
			usleep(10); // 这非常重要，不能发太快，否则客户端喘不过气。
		} else if (len == 0) {
			break;
		} else {
			log_error("read file error");
			return false;
		}
	}
#else
	int size = lseek(fd, 0, SEEK_END); // 从 0 移动到 end 偏移的字节量，即文件大小。
	lseek(fd, 0, SEEK_SET); // SEEK_SET 表示将 fd 相关文件的指针指向相对文件头+offset(这里是0)字节的位置。
	off_t offset = 0;
	while (offset < size) { // 由于 sendfile 函数的缓冲区也是有一定大小的，所以也要循环发送
		int ret = sendfile(cfd, fd, &offset, size - offset); // Linux 提供的较为高效的传输文件的函数。
															 // 这里 offset 是开始，发完会被修改为偏移到的位置。
		if (ret == -1 && errno != EAGAIN) {
			log_error("send file errror");
			return false;
		}
	}
#endif
	log_debug("send file success");
	close(fd);
	return true;
}

bool CommunicationTask::sendHeadMsg(int cfd, int status, const char *descr, const char *type, int length) {
	// 状态行
	char buf[4096] = {};
	log_debug("status=%d descr=%s\n", status, descr);
	sprintf(buf, "http/1.1 %d %s\r\n", status, descr); // 好函数
	// 响应头
	sprintf(buf + strlen(buf), "content-type: %s\r\n", type);
	sprintf(buf + strlen(buf), "content-length: %d\r\n\r\n", length);

	if (send(cfd, buf, strlen(buf), 0) < 0) {
		log_error("send error");
		return false;
	}
	log_debug("send success");

	return true;
}

const char *CommunicationTask::getFileType(const char *name) {
	log_debug("name=%s, getting file type...", name);
	const char *dot = strrchr(name, '.'); // 自右向左查找到第一个点，截取该点到 name 尾部分
	if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
		return "text/html; charset=utf-8";
	if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
		return "image/jpeg";
	if (strcmp(dot, ".gif") == 0)
		return "image/gif";
	if (strcmp(dot, ".png") == 0)
		return "image/png";
	if (strcmp(dot, ".css") == 0)
		return "text/css";
	if (strcmp(dot, ".au") == 0)
		return "audio/basic";
	if (strcmp(dot, ".wav") == 0)
		return "audio/wav";
	if (strcmp(dot, ".avi") == 0)
		return "video/x-msvideo";
	if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
		return "video/quicktime";
	if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
		return "video/mpeg";
	if (strcmp(dot, ".vrml") == 0)
		return "model/vrml";
	if (strcmp(dot, ".midi") == 0)
		return "audio/midi";
	if (strcmp(dot, ".mp3") == 0)
		return "audio/mp3"; // 还是mpeg?
	if (strcmp(dot, ".ogg") == 0)
		return "application/ogg";
	if (strcmp(dot, ".pac") == 0)
		return "application/x-ns-proxy-autoconfig";
	return "text/plain; charset=utf-8"; // 纯文本
}

bool CommunicationTask::sendDir(const char *dirName, int cfd) { // 发送格式详见“目录示例.html”
	char buf[4096] = {};
	sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirName);
	struct dirent **namelist; // 指向一个指针数组
	int num = scandir(dirName, &namelist, NULL, alphasort);
	for (int i = 0; i < num; i++) {
		// 取出文件名
		char *name = namelist[i]->d_name;
		struct stat st;
		char path[1024] = {};
		sprintf(path, "%s/%s", dirName, name);
		stat(path, &st);
		if (S_ISDIR(st.st_mode)) {
			// a标签 <a href="跳转地址">name</a> （如果是跳到目录里面则目录名后面要加一个“/”）
			sprintf(buf + strlen(buf), "<tr><td><a href=\"%s/\">%s</a></td><td>%ld</td></tr>", name, name,
					st.st_size); // st_size 是文件的大小（单位 byte）
		} else {
			sprintf(buf + strlen(buf), "<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>", name, name, st.st_size);
		}
		send(cfd, buf, strlen(buf), 0);
		memset(buf, 0, sizeof(buf)); // 每次发送完就清除，发送下次内容需要一个空的 buf
		free(namelist[i]);
	}
	sprintf(buf, "</table></body></html>");
	send(cfd, buf, strlen(buf), 0);
	free(namelist);

	return true;
}

int CommunicationTask::hexToDec(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return 0;
}

void CommunicationTask::decodeMsg(char *to, char *from) {
	while (*from != 0) {
		if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) {
			*to = hexToDec(from[1]) * 16 + hexToDec(from[2]);
			from += 3;
		} else {
			*to = *from;
			from++;
		}
		to++;
	}
	*to = 0;
}
