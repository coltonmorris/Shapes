#ifndef _circle_h_
#define _circle_h_

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle();
	Circle(const Point v1_in,const double radius_in,const Point colors_in);
	virtual ~Circle();
	void draw();
	virtual void save(std::ofstream &os)const;

	Point v1;
	double radius;
protected:
};

std::istream & operator>>(std::istream &is, Circle &c);


#endif /* _CIRCLE_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

