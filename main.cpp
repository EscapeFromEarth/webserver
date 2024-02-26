#include "iostream"
#include "unistd.h"
#include "utils/logger.h"
#include "utils/server.h"
#include "utils/threadPool.h"

using namespace abcpony::utility;

int main(int argc,
		 char *argv[]) { // argc为参数数量，argv为存参数（字符串指针）的数组的头（规定写法，实际上在终端用的时候传个数）
	// 这里希望客户（在终端启动程序）指定三个参数，分别是可执行程序名称、端口号、资源根目录。

	if (argc < 3) {
		printf("./a.out port path\n");
		return -1;
	}

	auto logger = Singleton<Logger>::instance();
	logger->open("/home/abcpony/myProjects/Reactor_cppversion/log/main.log");
	logger->set_max_size(1024);
	logger->set_level(Logger::LOG_INFO);
	logger->set_console(false);

	auto server = Singleton<Server>::instance(); // 创建服务器
	server->initThreadPool(3, 10);

	unsigned short port = atoi(argv[1]);
	chdir(argv[2]); // 将程序切换到资源根目录来，后面客户端请求资源的相对（根目录的）路径就可以直接用。
	server->initListenFD(port);
	server->epollRun();

	return 0;
}