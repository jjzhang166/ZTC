#ifndef ZTC_ZALLOCATOR_HPP
#define ZTC_ZALLOCATOR_HPP

#include <stddef.h>

namespace ZTC
{
	size_t* AllocCounter()
	{
		return ::new size_t;
	}

	void DeallocCounter(size_t* &ptr)
	{
		::delete ptr;
		ptr = NULL;
	}
}

#endif //ZTC_ZALLOCATOR_HPP