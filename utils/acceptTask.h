#pragma once

#include "utils/task.h"

namespace abcpony {
namespace utility {

class AcceptTask : public Task {
  public:
	AcceptTask();
	void execute();
	void destroy();
};

} // namespace utility
} // namespace abcpony
