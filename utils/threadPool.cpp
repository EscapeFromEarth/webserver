#include "utils/threadPool.h"
#include "utils/logger.h"
using namespace abcpony::utility;
#include "cstring"
#include "iostream"
#include "string"
#include "unistd.h"

const int NUMBER = 2;

ThreadPool::ThreadPool(int min, int max)
	: m_minNum(min), m_maxNum(max), m_busyNum(0), m_aliveNum(min), m_exitNum(0), m_shutdown(false) {
	do {
		m_taskQ = new TaskQueue;
		if (m_taskQ == nullptr) {
			// std::cout << "new TaskQueue fail ..." << std::endl;
			log_error("new TaskQueue fail ...");
			break;
		}
		log_debug("new TaskQueue success");
		m_threadIDs = new pthread_t[max];
		if (m_threadIDs == nullptr) {
			// std::cout << "new threadIDs fail..." << std::endl;
			log_error("new threadIDs fail ...");
			break;
		}
		log_debug("new threadIDs success");
		memset(m_threadIDs, 0, sizeof(pthread_t) * max);

		if (pthread_mutex_init(&m_lock, NULL) != 0 || pthread_cond_init(&m_notEmpty, NULL) != 0) {
			// std::cout << "mutex or condition init fail..." << std::endl;
			log_error("mutex or condition init fail ...");
			break;
		}
		log_debug("mutex and condition init success");

		// 创建线程
		pthread_create(&m_managerID, NULL, manager, this);
		for (int i = 0; i < min; i++) {
			pthread_create(m_threadIDs + i, NULL, worker, this);
			// std::cout << "build sonThread, ID: " << m_threadIDs[i] << std::endl;
			log_debug("build sonThread, ID: %ld", m_threadIDs[i]);
		}
		return;
	} while (0);

	delete m_taskQ; // 提示说delete nullptr是不会产生影响的。
	delete[] m_threadIDs;
}

ThreadPool::~ThreadPool() {
	// 首先要关掉
	m_shutdown = 1;
	// 阻塞回收管理者线程
	pthread_join(m_managerID, NULL); // 等待线程结束，并且负责回收线程资源
	// 唤醒阻塞的消费者
	int aliveNum = getAliveNum(); // 不出意外就是等于minNum
	for (int i = 0; i < aliveNum; i++) {
		pthread_cond_signal(&m_notEmpty);
	}
	sleep(1);
	// 释放堆内存
	if (m_taskQ)
		free(m_taskQ);
	if (m_threadIDs)
		free(m_threadIDs);
	// std::cout << "You just see where I am." << std::endl;
	log_debug("You just see where I am.");
	pthread_mutex_destroy(&m_lock);
	pthread_cond_destroy(&m_notEmpty);
}

void ThreadPool::addTask(Task *task) {
	pthread_mutex_lock(&m_lock);
	if (m_shutdown) {
		pthread_mutex_unlock(&m_lock);
		return;
	}
	m_taskQ->addTask(task);
	pthread_cond_signal(&m_notEmpty);
	pthread_mutex_unlock(&m_lock);
}

int ThreadPool::getBusyNum() {
	return m_busyNum;
}

int ThreadPool::getAliveNum() {
	return m_aliveNum;
}

void *ThreadPool::worker(void *arg) {
	ThreadPool *pool = static_cast<ThreadPool *>(arg);
	while (true) {
		pthread_mutex_lock(&pool->m_lock);
		while (!pool->m_shutdown && pool->m_taskQ->getTaskNumber() == 0) { // 队列为空
			pthread_cond_wait(&pool->m_notEmpty, &pool->m_lock);		   // 要阻塞该线程
			if (pool->m_exitNum > 0) { // 被唤醒之后判断一下是不是要叫我自杀
				pool->m_exitNum--;
				if (pool->m_aliveNum > pool->m_minNum) {
					pool->threadExit();
				}
			}
		} // 这里写在循环中是防止“虚假唤醒”，比如多个线程在等待，一广播大家都被唤醒了，但总可能有人还是得继续排队的，所以要再判断，不行再阻塞，如此循环。

		if (pool->m_shutdown) { // 如果关闭了（注意这个不能往上一段前面放，要有时间推移（它会改变）的概念）
			pool->threadExit();
		}

		// 从任务队列中取出一个任务
		Task *task = pool->m_taskQ->takeTask();
		pool->m_busyNum++;
		pthread_mutex_unlock(&pool->m_lock); // 解锁，到这里不用用到pool的__除了m_busyNum外__的内容了

		// std::cout << "thread " << std::to_string(pthread_self()) << " start working..." << std::endl;
		log_debug("thread %ld start working ...",
				  pthread_self()); // 咱也不知道为什么，这个就是输出 0，就是运行是没错的，日志有问题。。。
		task->execute(); // 在执行期间才会去锁住服务器的epfd那把锁，而此时已经放弃了线程池的锁，所以不会出现循环锁的问题。
		// std::cout << "thread " << pthread_self() << " end working..." << std::endl;
		log_debug("thread %ld end working", pthread_self());
		task->destroy();
		delete task;

		pthread_mutex_lock(&pool->m_lock);
		pool->m_busyNum--;
		pthread_mutex_unlock(&pool->m_lock);
	}
	return nullptr;
}

void ThreadPool::threadExit() // 调用时候线程是持有锁的
{
	pthread_t tid = pthread_self(); // 当前是哪个线程运行到这个语句，这个就会返回它的线程ID
	// std::cout << "threadExit() called, " << tid << " exiting..." << std::endl;
	log_debug("threadExit() called, %ld exiting", tid);
	for (int i = 0; i < m_maxNum; i++) {
		if (m_threadIDs[i] == tid) {
			m_threadIDs[i] = 0;
			break;
		}
	}
	m_aliveNum--;
	pthread_mutex_unlock(&m_lock);
	pthread_exit(NULL); // 线程自动结束自己，并且放弃资源
}

void *ThreadPool::manager(void *arg) {
	ThreadPool *pool = (ThreadPool *)arg;
	while (!pool->m_shutdown) { // emm这里没有锁住就去访问，行吧，可能因为问题不大。

		sleep(1); // 每隔1s就检查一次看用不用创建还是销毁线程

		//		pthread_mutex_lock(&pool->m_lock); // 为什么这里就加个锁？是因为读的太多？
		int queueSize = pool->m_taskQ->getTaskNumber();
		int liveNum = pool->getAliveNum();
		int busyNum = pool->getBusyNum();
		//		pthread_mutex_unlock(&pool->m_lock);

		// 如果需要，一次性创建 NUMBER 个（满了当然另当别论）
		if (queueSize > liveNum && liveNum < pool->m_maxNum) {
			pthread_mutex_lock(&pool->m_lock);
			int counter = 0;
			for (int i = 0; i < pool->m_maxNum && counter < NUMBER && pool->m_aliveNum < pool->m_maxNum;
				 i++) {							 // 注意这里要用pool->liveNum
				if (pool->m_threadIDs[i] == 0) { // 长整型
					pthread_create(pool->m_threadIDs + i, NULL, worker, pool);
					counter++;
					pool->m_aliveNum++;
				}
			}
			pthread_mutex_unlock(&pool->m_lock);
		}

		// 如果需要，一次性销毁 NUMBER 个（到minNum了当然另当别论）
		if (busyNum * 2 < liveNum && liveNum > pool->m_minNum) {
			pthread_mutex_lock(&pool->m_lock);
			pool->m_exitNum = NUMBER;
			pthread_mutex_unlock(&pool->m_lock);
			for (int i = 0; i < NUMBER; i++) {
				pthread_cond_signal(&pool->m_notEmpty); // 唤醒一个去自杀（里面会自动判定会不会自杀后live<min了）
			}
		}
	}
	return NULL;
}