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

namespace ZTC
{
   #define DELETE_PTR(Ptr)    {if(Ptr){delete Ptr; Ptr = NULL;}}
   #define ZTC_BREAK_IF(Pre) if(Pre)break
   #define ZTC_RETURN_IF(Pre) if(Pre)return

	enum PointState
	{
		NegativeX = 0,
		NegativeY,
		EqualPoint,
		PositiveX,
		PositiveY,
		BottomRight,   //����
		TopRight,
		TopLeft,
		BottomLeft,
		NoDefault,
		XAxis, //ͬһX��
		YAxis, //ͬһY��
		Overlap //�ص�
	};

	enum Tirstate
	{
		Negative = -1,
		Zore = 0,
		Positive = 1
	};

	enum {CHAR_COUNT = 255};
}
#endif //ZTC_ZBASE_H


