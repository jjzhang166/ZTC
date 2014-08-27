#ifndef ZTC_INCLUDE_ZTIME_H
#define ZTC_INCLUDE_ZTIME_H

#include <time.h>
#include <string>

using std::string;

namespace ZTC
{
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
		int seconds;
	};

	class ZDateTime
	{
	public:
		ZDateTime();

		ZDate GetDate();
		ZTime GetTime();
		string Format(const char* pCh, ...) const;

	private:
		time_t m_time;
		tm *m_tm;
		ZDate m_date;
		ZTime m_ztime;

	};
}

#endif //ZTC_INCLUDE_ZTIME_H