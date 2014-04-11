#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle();
	Triangle(const Point v1_in,const Point v2_in,const Point v3_in,const Point colors_in);
	virtual ~Triangle();
	void draw();
	virtual void save(std::ofstream &os)const;

	Point v1,v2,v3;
protected:
};

std::istream & operator>>(std::istream &is, Triangle &t);

#endif /* _TRIANGLE_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

