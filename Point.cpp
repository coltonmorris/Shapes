#include "Point.h"

Point::Point()
	:x(0),y(0),z(0)
{
}

Point::Point(const double &x_in, const double &y_in)
	:x(x_in),y(y_in),z(0)
{
}

Point::Point(const double &x_in, const double &y_in,const double &z_in)
	:x(x_in),y(y_in),z(z_in)
{
}
Point::Point(const Point &src)
	:x(0),y(0),z(0)
{
	*this = src;
}
//assignment overload
Point &Point::operator=(const Point &rhs){
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}








