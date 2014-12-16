#ifndef ZTC_ZCOUNTERPOLICY_HPP
#define ZTC_ZCOUNTERPOLICY_HPP

#include <stddef.h>
#include "ZAllocator.hpp"

namespace ZTC
{
	class ZSimpleReferenceCount
	{
	public:
		ZSimpleReferenceCount():m_pCounter(NULL)
		{}

		//template <typename T>
		void Init()
		{
			m_pCounter = AllocCounter();
			*m_pCounter = 1;
		}

		//template <typename T>
		void Dispose()
		{
			DeallocCounter(m_pCounter);
		}

		//template<typename T>
		void Increment()
		{
			++*m_pCounter;
		}

		//template<typename T>
		void Decrement()
		{
			--*m_pCounter;
		}

		//template<typename T>
		bool IsZero()
		{
			return *m_pCounter == 0;
		}

		size_t GetCounter()
		{
			return *m_pCounter;
		}

	private:
		size_t* m_pCounter;
	};
}

#endif //ZTC_ZCOUNTERPOLICY_HPP