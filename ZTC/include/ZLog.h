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
#define __FILENAME__ Log::getFileName(__FILE__)
#else
#define __FILENAME__ __FILE__
#endif

#define TRACE_DEBUG(format, ...)\
{\
	ZLog* pLog = ZLog::getInstance();\
	pLog->m_mutex.lock();\
	pLog->debug("%s %s:%d  ", "DEBUG", __FILENAME__, __LINE__);\
	pLog->debug(format, ##__VA_ARGS__);\
	pLog->m_mutex.unlock();\
}

#define TRACE_INFO(format, ...)\
{\
	ZLog* pLog = ZLog::getInstance();\
	pLog->m_mutex.lock();\
	pLog->info("%s %s:%d  ", "INFO", __FILENAME__, __LINE__);\
	pLog->info(format, ##__VA_ARGS__);\
	pLog->m_mutex.unlock();\
}

#define TRACE_WARN(format, ...)\
{\
	ZLog* pLog = ZLog::getInstance();\
	pLog->m_mutex.lock();\
	pLog->warn("%s %s:%d  ", "WARN", __FILENAME__, __LINE__);\
	pLog->warn(format, ##__VA_ARGS__);\
	pLog->m_mutex.unlock();\
}

#define TRACE_ERR(format, ...)\
{\
	ZLog* pLog = ZLog::getInstance();\
	pLog->m_mutex.lock();\
	pLog->error("%s %s:%d  ", "ERR", __FILENAME__, __LINE__);\
	pLog->error(format, ##__VA_ARGS__);\
	pLog->m_mutex.unlock();\
}

END_ZTC_NAMESPACE
#endif //ZTCTEST_INCLUDE_ZLOG_H