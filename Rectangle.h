#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(const Point v1_in,const Point v2_in,const Point colors_in);
	virtual ~Rectangle();
	virtual void draw();
	virtual void save(std::ofstream &os)const;

	Point v1,v2;
protected:
};

std::istream & operator>>(std::istream &is, Rectangle &r);

#endif /* _RECTANGLE_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

