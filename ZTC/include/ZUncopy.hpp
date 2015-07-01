/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZNonCopyAble.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.11.25 21:49:35
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.11.25 21:49:35
*/

#ifndef ZTC_INCLUDE_ZUNCOPY_H
#define ZTC_INCLUDE_ZUNCOPY_H

#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

class ZTC_CLASS ZUncopy
{
public:
	ZUncopy() {}
	~ZUncopy() {}
private:
	ZUncopy(const ZUncopy&);
	ZUncopy& operator= (const ZUncopy&);
};

END_ZTC_NAMESPACE

#endif //ZTC_INCLUDE_ZUNCOPY_H