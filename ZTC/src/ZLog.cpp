#include "../include/ZLog.h"
#include <cstdarg>
#include <cstdio>

BEGIN_ZTC_NAMESPACE
ZLog::ZLog() : m_writeStdout(false), m_logLevel(LOG_OFF), m_fileName(NULL)
{

}

ZLog::~ZLog()
{
	delete[] m_fileName;
	m_ofstream.close();
}

int ZLog::init(const char* fileName, LogLevel level, bool writeStdout)
{
	m_logLevel = level;
	m_writeStdout = writeStdout;
	std::string realFileName = std::string(fileName);
	fileName = realFileName.c_str();
	int strLen = strlen(fileName);
	m_fileName = new char[strLen + 1];
	if(!m_fileName)
		return -1;
	const_cast<char*>(m_fileName)[strLen] = 0;
	memcpy((char*)m_fileName, fileName, strLen);
	if(m_ofstream.is_open())
		m_ofstream.close();
	m_ofstream.open(m_fileName, std::ios::app);
	if(m_ofstream.is_open() == false)
		return -1;
	return 0;
}

int ZLog::init(const char* fileName, const char* level, bool writeStdout)
{
	if(strcmp(level, "all") == 0)
		return init(fileName, LOG_ALL, writeStdout);
	else if(strcmp(level, "trace") == 0)
		return init(level, LOG_TRACE);
	else if(strcmp(level, "debug") == 0)
		return init(fileName, LOG_DEBUG, writeStdout);
	else if(strcmp(level, "info") == 0)
		return init(fileName, LOG_INFO, writeStdout);
	else if(strcmp(level, "warn") == 0)
		return init(fileName, LOG_WARN, writeStdout);
	else if(strcmp(level, "error")== 0)
		return init(fileName, LOG_ERROR, writeStdout);
	else if(strcmp(level, "fatal")== 0)
		return init(fileName, LOG_FATAL, writeStdout);
	else if(strcmp(level, "off") == 0)
		return init(fileName, LOG_OFF, writeStdout);
	else
		return init(fileName, LOG_WARN, writeStdout);
}

bool ZLog::setLevel(LogLevel level)
{
	if(level < LOG_OFF || level > LOG_ALL)
		return false;
	m_logLevel = level;
	return true;
}

void ZLog::setLevel(const char* level)
{
	LogLevel l = LOG_OFF;
	bool flag = true;
	if(strcmp(level, "all") == 0)
		l = LOG_ALL;
	else if(strcmp(level, "trace") == 0)
		l = LOG_TRACE;
	else if(strcmp(level, "debug") == 0)
		l = LOG_DEBUG;
	else if(strcmp(level, "info"))
		l = LOG_INFO;
	else if(strcmp(level, "warn"))
		l = LOG_WARN;
	else if(strcmp(level, "error"))
		l = LOG_ERROR;
	else if(strcmp(level, "fatal"))
		l = LOG_FATAL;
	else if(strcmp(level, "off"))
		l = LOG_OFF;
	else
		flag = false;
	if(flag)
	{
		m_logLevel = l;
	}
}

void ZLog::logInformation(LogLevel level, const char *format, ...)
{
	va_list arg;
	va_start(arg, format);
	log(level, format, arg);
	va_end(arg);
}

void ZLog::log(LogLevel level, const char* format, va_list& arg)
{
	if(level > m_logLevel)
		return;
	static char buf[4096];
#ifndef _MSC_VER
	va_list temp;
	va_copy(temp, arg);
	int ret = vsnprintf(buf, sizeof(buf), format, arg);
	va_end(temp);
#else
	int ret = _vsnprintf(buf, sizeof(buf), format, arg);
#endif
	if(ret < 1)
		return;
	ret = ret > sizeof(buf) ? sizeof(buf) : ret;
	
	m_ofstream.write(buf, ret);
	if(m_writeStdout)
	{
		fputs(buf, stdout);
		fflush(stdout);
	}
}

const char* ZLog::getFileName(const char* fullName)
{
	while(*fullName)
		++fullName;
#ifdef _MSC_VER
	while(*--fullName != '\\')
#else
	while(*--fullName != '/')
#endif
		;
	return ++fullName;
}


END_ZTC_NAMESPACE