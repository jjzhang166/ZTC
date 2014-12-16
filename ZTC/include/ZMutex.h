#ifndef ZTC__INCLUDE__ZMUTEX_H
#define ZTC__INCLUDE__ZMUTEX_H

#include "ZMultiPlatformConfig.h"
#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE
#ifdef __GNUC__
	struct ZTC_CLASS ZMutex
	{
		ZMutex()
		{
			pthread_mutex_init(&m_mutex, NULL);
		}
		~ZMutex()
		{
			pthread_mutex_destroy(&m_mutex);
		}
		void lock()
		{
			pthread_mutex_lock(&m_mutex);
		}
		void trylock()
		{
			pthread_mutex_trylock(&m_mutex);
		}
		void unlock()
		{
			pthread_mutex_unlock(&m_mutex);
		}
		pthread_mutex_t m_mutex;
	};
#elif _MSC_VER
	struct ZTC_CLASS ZMutex
	{
		ZMutex()
		{
			InitializeCriticalSection(&m_mutex);
		}
		~ZMutex()
		{
			DeleteCriticalSection(&m_mutex);
		}
		void lock()
		{
			EnterCriticalSection(&m_mutex);
		}
		void unlock()
		{
			LeaveCriticalSection(&m_mutex);
		}
		void trylock()
		{
			TryEnterCriticalSection(&m_mutex);
		}
		CRITICAL_SECTION m_mutex;
	};
#else
	#error "unsupport compile!!!"
#endif

struct ZTC_CLASS ZAutoMutex
{
	ZAutoMutex(ZMutex* mutex):m_mutex(mutex)
	{
		m_mutex->lock();
	}
	~ZAutoMutex()
	{
		m_mutex->unlock();
	}
	ZMutex* m_mutex;
};

END_ZTC_NAMESPACE
#endif//ZTC__INCLUDE__ZMUTEX_H