/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZAllocate.hpp
* File Identifier :
* Abstract        
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.11.21 22:32:43
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.11.21 22:32:43
*/

#ifndef ZTC_ALGORITHM_INCLUDE_Z_ALLOCATE_HPP
#define ZTC_ALGORITHM_INCLUDE_Z_ALLOCATE_HPP

#include "../../include/ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

class ZAllocate
{
public:
	template<typename T>
	T* Allocte()
	{
		return new T();
	}
};

END_ZTC_NAMESPACE
#endif //ZTC_ALGORITHM_ZALLOCATE_HPP