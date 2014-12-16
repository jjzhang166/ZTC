#include "..\include\ZPoint.h"

#include <math.h>

namespace ZTC
{
	ZPoint::ZPoint():x(0),y(0)
	{
	
	}
	ZPoint::ZPoint(int valueX, int valueY):x(valueX), y(valueY)
	{}
	ZPoint::ZPoint(const ZPoint &other):x(other.x),y(other.y)
	{}
	ZPoint& ZPoint::operator=(const ZPoint &other)
	{
		if(this == &other)
			return *this;
		x = other.x;
		y = other.y;
		return *this;
	}

	ZPoint::~ZPoint()
	{}

	ZPoint ZPoint::operator+= (const ZPoint &other)
	{
		return ZPoint(x += other.x, y += other.y);
	}
	ZPoint ZPoint::operator-= (const ZPoint &other)
	{
		return ZPoint(x -= other.x, y -= other.y);
	}

	bool operator==(const ZPoint &one, const ZPoint &two)
	{
		if(one.x == two.x && one.y == two.y)
			return true;
		return false;
	}
	bool operator!=(const ZPoint &one, const ZPoint &two)
	{
		if(one.x == two.x && one.y == two.y)
			return false;
		return true;
	}

	PointState operator<(const ZPoint &one, const ZPoint &two)
	{
		return ComparePoint(one, two);
	}
	PointState operator>(const ZPoint &one, const ZPoint &two)
	{
		return ComparePoint(one, two);
	}

	ZPoint operator+(const ZPoint &one, const ZPoint &two)
	{
		return ZPoint(one.x + two.x, one.y + two.y);
	}
	ZPoint operator-(const ZPoint &one, const ZPoint &two)
	{
		return ZPoint(one.x - two.x, one.y - two.y);
	}

	PointState ComparePoint(const ZPoint &one, const ZPoint &two)
	{
		if(one.x == two.x && one.y == two.y)
			return EqualPoint;

		if(one.x == two.x && one.y > two.y)
			return PositiveY;
		if(one.x == two.x && one.y < two.y)
			return NegativeY;
	
		if(one.x > two.x && one.y == two.y)
			return PositiveX;
		if(one.x< two.x && one.y == two.y)
			return NegativeX;

		if(one.x > two.x && one.y > two.y)
			return BottomRight;
		if(one.x > two.x && one.y <two.y)
			return TopRight;

		if(one.x < two.x && one.y > two.y)
			return BottomLeft;
		if(one.x < two.x && one.y <two.y)
			return TopLeft;

		return NoDefault;
	}

	PointState ZPoint::IsOnSameLine(const ZPoint &one, const ZPoint &two)
	{
		PointState state = NoDefault;
		//在同一X轴上
		if(abs(one.x - two.x) >0 && abs(one.y - two.y) == 0 ) 
			state = XAxis;

		//在同一Y轴上
		if(abs(one.x - two.x) == 0 && abs(one.y - two.y) >0 ) 
			state = YAxis;

		//重叠
		if(abs(one.x - two.x) == 0 && abs(one.y - two.y) == 0)
			state = Overlap;
		return state;
	}

	ZPoint ZPoint::SymmetryOfOpint(const ZPoint &point)
	{
		return ZPoint(2 * point.x - x, 2 * point.y - y);
	}

	double ZPoint::Distance(const ZPoint &other)
	{
		return sqrt(pow((double)(x - other.x), 2) + pow((double)(y - other.y), 2));
	}
}