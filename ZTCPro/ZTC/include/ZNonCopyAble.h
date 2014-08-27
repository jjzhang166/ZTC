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

class ZUncopy
{
public:
	ZUncopy() {}
	~ZUncopy() {}
private:
	ZUncopy(const ZUncopy&);
	ZUncopy& operator= (const ZUncopy&);
};

#endif //ZTC_INCLUDE_ZUNCOPY_H