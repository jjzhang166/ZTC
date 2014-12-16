#include "ZClientTimer.h"

BEGIN_ZTC_NAMESPACE
uint32_t get_time_ms()
{
#ifdef __GNUC__
	timeval now;
	gettimeofday(&now, NULL);
	return now.tv_sec * 1000 + (now.tv_usec / 1000);
#elif _MSC_VER
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return uint32_t ((double)counter.QuadPart/frequency.QuadPart * 1000);
#endif
}

void sleep_ms(int ms)
{
#ifdef __GNUC__
	usleep(ms * 1000);
#elif _MSC_VER
	Sleep(ms);
#endif
}
const char* mCh[] ={
	"%y",
	"%m",
	"%d", 
	"%h"
};
END_ZTC_NAMESPACE