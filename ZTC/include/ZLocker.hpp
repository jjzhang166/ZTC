#ifndef ZTC__INCLUDE__ZLOCKER_HPP
#define ZTC__INCLUDE__ZLOCKER_HPP

#include "ZGlobalDefine.h"

#ifdef Z_OS_WIN32
#include <windows.h>
#include <afxmt.h>
#elif defined(Z_OS_LINUX) 
#endif 

namespace ZTC
{
	class ZLocker
	{
	public:
		ZLocker()
		{
#ifdef Z_OS_WIN32
			m_mutex = CreateMutex(NULL, TRUE);
#elif defined(Z_OS_LINUX)
#endif //
		}

		~ZLocker()
		{
#ifdef Z_OS_WIN32
			::CloseHandle(m_mutex);
#endif //
		}

		void lock()
		{
			#ifdef Z_OS_WIN32
			::WaitForSingleObject(m_mutex, INFINITE);
			#endif //
		}
		void unlock()
		{
			#ifdef Z_OS_WIN32
			::ReleaseMutex(m_mutex);
			#endif //
		}
	private:
#ifdef Z_OS_WIN32
		CMutex m_mutex;
#endif //
	};
}

#endif //ZTC__INCLUDE__ZLOCKER_HPP