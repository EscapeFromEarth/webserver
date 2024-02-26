#pragma once

namespace abcpony{
	namespace utility{
		class Task {
		public:
			Task(void* arg);
			virtual ~Task();
			virtual void execute() = 0;
			virtual void destroy() = 0;

		protected:
			void *arg;
		};
	}
}