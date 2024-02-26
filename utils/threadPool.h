#pragma once
#include "pthread.h"
#include "queue"
#include "utils/taskQueue.h"

namespace abcpony {
	namespace utility {
		class ThreadPool {
		public:
			ThreadPool(int min, int max);
			~ThreadPool();

			void addTask(Task *task);

			int getBusyNum();
			int getAliveNum();

		private:
			static void *worker(void *arg);
			static void *manager(void *arg);
			void threadExit();

		private:
			pthread_mutex_t m_lock;
			pthread_cond_t m_notEmpty; // 任务队列是不是空了
			pthread_t* m_threadIDs; // 工作者线程ID
			pthread_t m_managerID; // 管理者线程ID
			TaskQueue *m_taskQ;
			int m_minNum; // 最小线程数
			int m_maxNum; // 最大线程数
			int m_busyNum; // 忙线程数
			int m_aliveNum;
			int m_exitNum; // 要销毁的线程数
			bool m_shutdown; // 是否要销毁线程池
		};
	}
}