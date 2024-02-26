#include "utils/logger.h"
using namespace abcpony::utility;

const char *Logger::s_level[LOG_COUNT] = {
		"DEBUG",
		"INFO",
		"WARN",
		"ERROR",
		"FATAL"
};

void Logger::open(const string &filename) {
	m_filename = filename;
	m_ofs.open(filename.c_str(), std::ios::app); // 追加方式
	if (m_ofs.fail()) {
		throw std::logic_error("open log file failed: " + filename);
	}
	m_ofs.seekp(0, std::ios::end); // 把指针放到文件末尾，虽然上面有说ios::app，但是通常会出错。。
	m_len = (int) m_ofs.tellp();
}

void Logger::close() {
	m_ofs.close();
}

void Logger::log(Level level, const char *file, int line, const char *format, ...) {
	if (m_level > level)return; // 等级低于日志等级的消息不做记录
	if (m_ofs.fail()) {
		throw std::logic_error("open log file failed: " + m_filename);
	}
	std::ostringstream oss;
	time_t ticks = time(nullptr); // 时间戳
	struct tm time_info = {};
	localtime(&time_info, &ticks);
	char timestamp[32] = {};
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H-%M-%S", &time_info); // 日期 时间点

	int len = 0;
	const char *fmt = "%s %s %s:%d "; // 日期时间 等级 文件:行号
	len = snprintf(nullptr, 0, fmt, timestamp, s_level[level], file, line); // 通过这样的方式可以获取信息的长度
	if (len > 0) {
		char *buffer = new char[len + 1];
		snprintf(buffer, len + 1, fmt, timestamp, s_level[level], file, line);
		buffer[len] = 0; // 末尾赋值为 0
		oss << buffer;
		m_len += len;
		delete[]buffer;
	}

	va_list arg_ptr; // 可变参数列表的指针
	va_start(arg_ptr, format); // 让 arg_ptr 指向 format 后面的第一个参数
	auto tmp = arg_ptr;
	len = vsnprintf(nullptr, 0, format, arg_ptr);
	if (len > 0) {
		char *buffer = new char[len + 1];
		assert(tmp == arg_ptr); // 说明指针指向位置没有变化
		vsnprintf(buffer, len + 1, format, arg_ptr);
		buffer[len] = 0;
		oss << buffer;
		m_len += len;
		delete[]buffer;
	}
	va_end(arg_ptr); // 用完可变参数列表指针要记得调用这个东西
	oss << "\n";
	const string &str = oss.str();
	m_ofs << str;
	m_ofs.flush(); // 这样才能更新到磁盘上，使我待会一打开文件就能看到最新结果。
	if (m_console) {
		std::cout << str;
	}
	if (m_max > 0 && m_len >= m_max) {
		rotate();
	}
}

void Logger::set_level(int level) {
	m_level = level;
}

void Logger::set_console(bool console) {
	m_console = console;
}

void Logger::set_max_size(int bytes) {
	m_max = bytes;
}

void Logger::rotate() {
	close();
	sleep(1000);
	time_t ticks = time(nullptr);
	struct tm time_info = {};
	localtime(&time_info, &ticks);
	char timestamp[32] = {};
	strftime(timestamp, sizeof(timestamp), ".%Y-%m-%d_%H-%M-%S", &time_info);
	string filename = m_filename + timestamp;
	if (rename(m_filename.c_str(), filename.c_str()) != 0) {
		throw std::logic_error("rename file error: old is " + m_filename + ", new is " + filename);
	}
	open(m_filename);
}

void Logger::sleep(int milliseconds) {
#ifdef WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}

void Logger::localtime(struct tm *time_info, const time_t *ticks) {
#ifdef WIN32
	localtime_s(time_info, ticks);
#else
	localtime_r(ticks, time_info);
#endif
}