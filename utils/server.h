#pragma once

#include "utils/threadPool.h"
#include "utils/logger.h"
#include "utils/acceptTask.h"
#include "utils/communicationTask.h"
#include "pthread.h"

namespace abcpony {
namespace utility {

class Server {
	SINGLETON(Server);

	friend class AcceptTask;
	friend class CommunicationTask;

  public:
	// 初始化线程池
	bool initThreadPool(int min, int max);
	// 初始化监听的 socket
	bool initListenFD(unsigned short port);
	// 启动 epoll
	bool epollRun();

  private:
	// 和客户端建立连接
	bool acceptClient();

	// 接收http请求（数据交流）
	bool recvHttpRequest(int cfd);

  private:
	pthread_mutex_t m_epfd_lock; // 访问 m_epfd 需要拥有锁
	int m_lfd = -1;
	int m_epfd = -1;
	ThreadPool *m_threadpool;
};

} // namespace utility
} // namespace abcpony
