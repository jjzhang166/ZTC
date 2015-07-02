#ifndef ZTCTEST_INCLUDE_ZLOG_H
#define ZTCTEST_INCLUDE_ZLOG_H

#include "ZMacroDefine.h"
#include "ZSingleton.hpp"
#include "ZMutex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

BEGIN_ZTC_NAMESPACE

using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

class ZTC_CLASS ZLog : public ZSingleton<ZLog>
{
public:

	enum LogLevel
	{
		LOG_ALL,
		LOG_DEBUG,
		LOG_INFO,
		LOG_WARN,
		LOG_ERROR,
		LOG_NONE,
	};

	ZLog();
	~ZLog();
	
	int init(const char* fileName, LogLevel level = LOG_WARN, bool writeStdout = true);
	int init(const char* fileName, const char* level = "warn", bool writeStdout = true);

	bool setLevel(LogLevel level);
	void setLevel(const char* level);

	void debug(const char* format, ...);
	void info(const char* format, ...);
	void warn(const char* format, ...);
	void error(const char* format, ...);

	static const char* getFileName(const char* fullName);

private:
	void log(LogLevel level, const char* format, va_list& arg);

	const char* m_fileName;
	ofstream m_ofstream;
	LogLevel m_logLevel;
	bool m_writeStdout;

public:
	ZMutex m_mutex;
};

#ifdef _MSC_VER
#define __FILENAME__ ZLog::getFileName(__FILE__)
#else
#define __FILENAME__ __FILE__
#endif

#define TRACE_DEBUG(format, ...)\
{\
	ZLog::getInstance().m_mutex.lock();\
	ZLog::getInstance().debug("[%s] (%s:%d)", "DEBUG", __FILENAME__, __LINE__);\
	ZLog::getInstance().debug(format, ##__VA_ARGS__);\
	ZLog::getInstance().m_mutex.unlock();\
}

#define TRACE_INFO(format, ...)\
{\
	ZLog::getInstance().m_mutex.lock();\
	ZLog::getInstance().info("[%s] (%s:%d)", "INFO", __FILENAME__, __LINE__);\
	ZLog::getInstance().info(format, ##__VA_ARGS__);\
	ZLog::getInstance().m_mutex.unlock();\
}

#define TRACE_WARN(format, ...)\
{\
	ZLog::getInstance().m_mutex.lock();\
	ZLog::getInstance().warn("[%s] (%s:%d)", "WARN", __FILENAME__, __LINE__);\
	ZLog::getInstance().warn(format, ##__VA_ARGS__);\
	ZLog::getInstance().m_mutex.unlock();\
}

#define TRACE_ERR(format, ...)\
{\
	ZLog::getInstance().m_mutex.lock();\
	ZLog::getInstance().error("[%s] (%s:%d)", "ERROR", __FILENAME__, __LINE__);\
	ZLog::getInstance().error(format, ##__VA_ARGS__);\
	ZLog::getInstance().m_mutex.unlock();\
}

END_ZTC_NAMESPACE
#endif //ZTCTEST_INCLUDE_ZLOG_H