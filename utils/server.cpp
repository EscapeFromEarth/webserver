#define _GNU_SOURCE // 这句声明使用 GNU 扩展，然后就可以使用那个 alphasort 函数了（准确来说是解决掉爆红线问题）。

#include "utils/server.h"
#include "utils/threadPool.h"
using namespace abcpony::utility;

#include "arpa/inet.h"
#include "assert.h"
#include "cstring"
#include "ctype.h"
#include "dirent.h"
#include "errno.h"
#include "fcntl.h"
#include "server.h"
#include "stdlib.h"
#include "sys/epoll.h"
#include "sys/sendfile.h"
#include "sys/stat.h"
#include "unistd.h"

bool Server::initThreadPool(int min, int max) {
	m_threadpool = new ThreadPool(min, max);
	return true;
}

bool Server::initListenFD(unsigned short port) {

	int lfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lfd == -1) {
		log_error("create lfd error");
		return false;
	}
	log_debug("create lfd success");

	m_lfd = lfd;

	// 设置端口复用（实际应用中的系统不应该开启这个东西，只是为了方便调试）
	int opt = 1; // 为 1 表示启用，为 0 表示停用。
	int ret = setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (ret == -1) {
		log_error("set socket reuse error");
		return false;
	}
	log_warn("set socket reuse success");
	// ----------

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // 这个表示监听主机的所有网卡
	ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1) {
		log_error("bind address error");
		return false;
	}
	log_debug("bind address success");

	ret = listen(lfd, 128);
	if (ret == -1) {
		log_error("listen error");
		return false;
	}
	log_debug("start listening ...");

	return true;
}

bool Server::epollRun() {
	int epfd = epoll_create(1);
	if (epfd == -1) {
		log_error("create epoll error");
		return false;
	}
	log_debug("create epoll success");

	m_epfd = epfd;

	struct epoll_event ev;
	ev.data.fd = m_lfd; // data 是一个联合体，联合体的几个属性是共用一块内存的，也就是几个属性只能选一个使用。
	ev.events = EPOLLIN | EPOLLET; // 这里要设置为边沿触发模式，否则下面对于一个accept会在多次循环中发现然后添加了多次任务，导致莫名的错误。
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, m_lfd, &ev);
	if (ret == -1) {
		log_error("epoll ctl error");
		return false;
	}
	log_debug("epoll ctl success");

	const int size = 1024;
	struct epoll_event evs[size];
	while (1) {
		int num = epoll_wait(epfd, evs, size, -1);
		if (num == -1) {
			log_error("epoll wait error");
			return false;
		}
		log_debug("epoll wait success, num=%d", num);
		for (int i = 0; i < num; i++) {
			int fd = evs[i].data.fd;
			if (fd == m_lfd) {
				acceptClient();
			} else {
				recvHttpRequest(fd); // 接收数据，http 请求报文格式
			}
		}
	}

	return true;
}

bool Server::acceptClient() {
	// 在线程池里面添加一个accept任务
	m_threadpool->addTask(new AcceptTask());
	return true;
}

bool Server::recvHttpRequest(int cfd) {

	// 在线程池里面添加一个communication任务。
	m_threadpool->addTask(new CommunicationTask(new int(cfd)));
	return true;
}