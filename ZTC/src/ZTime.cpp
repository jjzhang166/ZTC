#include "../include/ZTime.h"
#include "../include/ZCommonality.h"
#include "../include/ZType.h"
#include <vector>
#include <stdarg.h>

BEGIN_ZTC_NAMESPACE;
ZDateTime::ZDateTime()
{
	
	
}



void getSystemDateTime(ZDateTime& dateTime)
{
	struct timeb tp;
	ftime (&tp);
	dateTime.msec = tp.millitm;
	tm *pTm = localtime(&tp.time);
	dateTime.second = pTm->tm_sec;
	dateTime.minute = pTm->tm_min;
	dateTime.hour = pTm->tm_hour;
	dateTime.day = pTm->tm_mday;
	dateTime.month = pTm->tm_mon + 1;
	dateTime.year = pTm->tm_year + 1900;
	dateTime.yDay = pTm->tm_yday;
	dateTime.weekDay = pTm->tm_wday;
	dateTime.isDst = pTm->tm_isdst;
}

END_ZTC_NAMESPACE;