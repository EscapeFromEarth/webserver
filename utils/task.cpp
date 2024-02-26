#include "task.h"
using namespace abcpony::utility;

Task::~Task() {}

Task::Task(void *arg) {
	this->arg = arg;
}