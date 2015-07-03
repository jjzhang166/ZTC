#ifndef ZTC_INCLUDE_ZTIME_H
#define ZTC_INCLUDE_ZTIME_H

#include <sys/timeb.h>
#include <time.h>
#include <string>
#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE;
using std::string;


class ZDateTime
{
public:
	ZDateTime();
	
	
	
	unsigned int msec;		///< 毫秒
	unsigned short second;	///< 秒(0-59)				
	unsigned short minute;	///< 分(0-59)				
	unsigned short hour;	///< 时(0-23)				
	unsigned short day;		///< 日(1-31)				
	unsigned short month;	///< 月(1-12)				
	unsigned short year;	///< 年(2000表示2000年)		
	unsigned short weekDay;	///< 星期					
	unsigned short yDay;	///< 年中的第几天			
	bool isDst;	///< 夏时制	
private:
	time_t m_time;
	tm *m_tm;
};

ZTC_API void getSystemDateTime(ZDateTime& dateTime);
ZTC_API unsigned long getTickCount();
ZTC_API unsigned long getThreadTime();

END_ZTC_NAMESPACE
#endif //ZTC_INCLUDE_ZTIME_H