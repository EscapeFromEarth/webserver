#pragma once
#include "utils/task.h"
#include "pthread.h"
#include "queue"

namespace abcpony {
	namespace utility {
		class TaskQueue {
		public:
			TaskQueue();
			~TaskQueue();

			void addTask(Task *task);

			Task *takeTask(); // 取出一个任务

			int getTaskNumber();

		private:
			pthread_mutex_t m_mutex; // 互斥锁
			std::queue<Task *> m_queue;
		};
	}
}
