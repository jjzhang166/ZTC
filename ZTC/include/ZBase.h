/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZBase.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : Geoffrey 
* Completion Date : 2013.7.21 18:26:20
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.7.21 18:26:20
*/

#ifndef ZTC_ZBASE_H
#define ZTC_ZBASE_H

#include "../include/ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE
#define DELETE_PTR(Ptr)    {if(Ptr){delete Ptr; Ptr = NULL;}}
#define BREAK_IF(Pre) if(Pre)break
#define RETURN_IF(Pre) if(Pre)return

enum PointState
{
	NegativeX = 0,
	NegativeY,
	EqualPoint,
	PositiveX,
	PositiveY,
	BottomRight,   //右下
	TopRight,
	TopLeft,
	BottomLeft,
	NoDefault,
	XAxis, //同一X轴
	YAxis, //同一Y轴
	Overlap //重叠
};

enum Tirstate
{
	Negative = -1,
	Zore = 0,
	Positive = 1
};

enum {CHAR_COUNT = 255};
END_ZTC_NAMESPACE
#endif //ZTC_ZBASE_H



