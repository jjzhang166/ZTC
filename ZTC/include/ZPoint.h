/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZPoint.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.7.21 18:15:42
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.7.21 18:15:42
*/

#ifndef ZTC_ZPOINT_H
#define ZTC_ZPOINT_H

#include "ZBase.h"

namespace ZTC
{
	class ZPoint
	{
	public:
		ZPoint();
		ZPoint(int valueX, int valueY);
		ZPoint(const ZPoint &other);
		ZPoint& operator=(const ZPoint &other);

		~ZPoint();

		ZPoint operator+= (const ZPoint &other);
		ZPoint operator-= (const ZPoint &other);

		friend bool operator==(const ZPoint &one, const ZPoint &two);
		friend bool operator!=(const ZPoint &one, const ZPoint &two);

		friend PointState operator<(const ZPoint &one, const ZPoint &two);
		friend PointState operator>(const ZPoint &one, const ZPoint &two);

		friend ZPoint operator+(const ZPoint &one, const ZPoint &two);
		friend ZPoint operator-(const ZPoint &one, const ZPoint &two); 
		
		friend PointState ComparePoint(const ZPoint &one, const ZPoint &two);

		//--@是否在同一条线上
		PointState IsOnSameLine(const ZPoint &one, const ZPoint &tow);

		//--@关于点对称
		ZPoint SymmetryOfOpint(const ZPoint &point);

		//--@点到点的距离
		double Distance(const ZPoint &other);

		int x;
		int y;
	};
}

#endif //ZTC_ZPOINT_H



