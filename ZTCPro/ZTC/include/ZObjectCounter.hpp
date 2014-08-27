/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZObjectCounter.hpp
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.2.20 22:41:50
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.2.20 22:41:50
*/

#ifndef ZTC__INCLUDE__ZOBJECTCOUNTER_HPP
#define ZTC__INCLUDE__ZOBJECTCOUNTER_HPP

#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

template <typename CountedType>
class ZObjectCounter
{
private: 
	static size_t m_count;

	ZObjectCounter()
	{
		++ZObjectCounter<CountedType>::m_count;
	}

	ZObjectCounter(ZObjectCounter<CountedType> const &)
	{
		++ZObjectCounter<CountedType>::m_count;
	}

	~ZObjectCounter()
	{
		--ZObjectCounter<CountedType>::m_count;
	}

public:
	static size_t liveNum()
	{
		return ZObjectCounter<CountedType>::m_count;
	}
};

template <typename CountedType>
size_t ZObjectCounter<CountedType>::m_count = 0;

END_ZTC_NAMESPACE

#endif //ZTC__INCLUDE__ZOBJECTCOUNTER_HPP