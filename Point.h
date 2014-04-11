#ifndef _POINT_H_
#define _POINT_H_

class Point
{
public:
	Point();
	//for x,y points
	Point(const double &x_in,const double &y_in);
	//for color values
	Point(const double &x_in,const double &y_in,const double &z_in);
	//copy constructor
	Point(const Point &src);
	//assignment operator
	Point &operator=(const Point &rhs);
	double x,y,z;
};



#endif /* _POINT_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

