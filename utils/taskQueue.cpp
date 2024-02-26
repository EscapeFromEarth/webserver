#include "taskQueue.h"
using namespace abcpony::utility;

TaskQueue::TaskQueue() {
	pthread_mutex_init(&m_mutex, NULL);
}

TaskQueue::~TaskQueue() {
	pthread_mutex_destroy(&m_mutex);
}

void TaskQueue::addTask(Task *task) {
	pthread_mutex_lock(&m_mutex);
	m_queue.push(task);
	pthread_mutex_unlock(&m_mutex);
}

Task *TaskQueue::takeTask() {
	Task *t;
	pthread_mutex_lock(&m_mutex);
	if (m_queue.size() > 0) {
		t=m_queue.front();
		m_queue.pop();
	}
	pthread_mutex_unlock(&m_mutex);
	return t;
}

int TaskQueue::getTaskNumber() {
	return m_queue.size(); // 读方面一般不加锁。
}