#include "utils/acceptTask.h"
#include "arpa/inet.h"
#include "fcntl.h"
#include "pthread.h"
#include "server.h"
#include "sys/epoll.h"
using namespace abcpony::utility;

AcceptTask::AcceptTask() : Task(nullptr) {
}

void AcceptTask::execute() {
	log_debug("accept task run");

	auto server = Singleton<Server>::instance();
	int cfd = accept(server->m_lfd, NULL, NULL);
	if (cfd == -1) {
		log_error("accept error");
		return;
	}
	// std::cout<<"???cfd="<<cfd<<std::endl;
	log_debug("accept success, cfd=%d", cfd);

	int flag = fcntl(cfd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(cfd, F_SETFL, flag);

	struct epoll_event ev;
	ev.data.fd = cfd;
	ev.events = EPOLLIN | EPOLLET;
	pthread_mutex_lock(&server->m_epfd_lock);
	int ret = epoll_ctl(server->m_epfd, EPOLL_CTL_ADD, cfd, &ev);
	pthread_mutex_unlock(&server->m_epfd_lock);
	if (ret == -1) {
		log_error("epoll ctl error");
		return;
	}
	log_debug("epoll ctl success");
}

void AcceptTask::destroy() {
	log_debug("accept task destroy");
}
