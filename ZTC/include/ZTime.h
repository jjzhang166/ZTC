#ifndef ZTC_INCLUDE_ZTIME_H
#define ZTC_INCLUDE_ZTIME_H

#include <time.h>
#include <string>
#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE;
using std::string;

struct ZDate
{
	int year;
	int month;
	int day;
	int weekDay;
};

struct ZTime
{
	int hour;
	int minute;
	int second;
};

class ZDateTime
{
public:
	ZDateTime();

	ZDate getDate();
	ZTime getTime();
	string format(const char* pCh) const;

private:
	time_t m_time;
	tm *m_tm;
	ZDate m_date;
	ZTime m_ztime;

};
END_ZTC_NAMESPACE
#endif //ZTC_INCLUDE_ZTIME_H