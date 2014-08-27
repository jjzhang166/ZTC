#include "../include/ZTime.h"
#include "../include/ZCommonality.h"
#include <vector>
#include <stdarg.h>

namespace ZTC
{
	const char* mCh[] ={
		"%y",
		"%m",
		"%d", 
		"%h"
	};

	ZDateTime::ZDateTime()
	{
		m_time = time(NULL);
		m_tm = localtime(&m_time);
		GetDate();
		GetTime();
	}

	ZDate ZDateTime::GetDate()
	{
		m_date.year = m_tm->tm_year;
		m_date.month = m_tm->tm_mon;
		m_date.day = m_tm->tm_mday;
		m_date.weekDay = m_tm->tm_wday;
		return m_date;
	}

	ZTime ZDateTime::GetTime()
	{
		m_ztime.hour = m_tm->tm_hour;
		m_ztime.minute = m_tm->tm_min;
		m_ztime.seconds = m_tm->tm_sec;
		return m_ztime;
	}

	string ZDateTime::Format(const char* pCh, ...) const
	{
		return string();
	}
}