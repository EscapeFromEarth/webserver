#pragma once

#include "utils/task.h"

namespace abcpony {
namespace utility {

class CommunicationTask : public Task {
  public:
	CommunicationTask(int *cfd);
	void execute();
	void destroy();

  private:
	bool parseRequestLine(const char *line, int cfd);
	// 发送文件
	bool sendFile(const char *filename, int cfd);
	// 发送目录
	bool sendDir(const char *dirName, int cfd);
	// 发送响应行 + 响应头
	bool sendHeadMsg(int cfd, int status, const char *descr, const char *type,
					 int length); // descr 是状态描述；后面是键值对（一般就两行，一个文件类型
								  // 和一个文件大小，如果不知道文件大小还可以不用发）。
	// 根据文件后缀映射文件类型
	const char *getFileType(const char *name);
	// 将字符转换为整形数字（单个位）
	int hexToDec(char c);
	// 解码（编码方式是UTF-8）
	void decodeMsg(char *to, char *from);
};

} // namespace utility
} // namespace abcpony
