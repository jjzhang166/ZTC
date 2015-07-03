#ifndef ZTCTEST_INCLUDE_ZLOG_H
#define ZTCTEST_INCLUDE_ZLOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ZMacroDefine.h"
#include "ZSingleton.hpp"
#include "ZMutex.h"
#include "ZTime.h"

BEGIN_ZTC_NAMESPACE

using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

enum LogLevel
{
	LOG_OFF,
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG,
	LOG_TRACE,
	LOG_ALL
};

class ZTC_CLASS ZLog : public ZSingleton<ZLog>
{
public:
	ZLog();
	~ZLog();
	
	int init(const char* fileName, LogLevel level = LOG_WARN, bool writeStdout = true);
	int init(const char* fileName, const char* level = "warn", bool writeStdout = true);

	bool setLevel(LogLevel level);
	void setLevel(const char* level);
	
	void logInformation(LogLevel level, const char *format, ...);
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

#define ZLOG_LOG(level, format, ...) \
{\
	ZLog::getInstance().m_mutex.lock();\
	ZDateTime date;\
	getSystemDateTime(date);\
	ZLog::getInstance().logInformation(level, "[%04d-%02d-%02d %02d:%02d:%02d:%03d]",\
			date.year, date.month, date.day, \
			date.hour, date.minute, date.second, date.msec);\
	char *pFormat = "[%s] %s:%d - ";\
	switch(level) \
	{\
	case LOG_FATAL: \
		ZLog::getInstance().logInformation(level, pFormat, "FATAL", __FILENAME__, __LINE__);\
		break;\
	case LOG_ERROR: \
		ZLog::getInstance().logInformation(level, pFormat, "ERROR", __FILENAME__, __LINE__);\
		break;\
	case LOG_WARN: \
		ZLog::getInstance().logInformation(level, pFormat, "WARN", __FILENAME__, __LINE__);\
		break;\
	case LOG_INFO: \
		ZLog::getInstance().logInformation(level, pFormat, "INFO", __FILENAME__, __LINE__);\
		break;\
	case LOG_DEBUG: \
		ZLog::getInstance().logInformation(level, pFormat, "DEBUG", __FILENAME__, __LINE__);\
		break;\
	case LOG_TRACE: \
		ZLog::getInstance().logInformation(level, pFormat, "TRACE", __FILENAME__, __LINE__);\
		break;\
	}\
	ZLog::getInstance().logInformation(level, format, ##__VA_ARGS__);\
	ZLog::getInstance().m_mutex.unlock();\
}

END_ZTC_NAMESPACE
#endif //ZTCTEST_INCLUDE_ZLOG_H