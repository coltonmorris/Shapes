#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Point.h"
#include <cmath>
#include <iostream>
#include <fstream>
#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif

class Shape
{
public:
	Shape();
	Shape(const Point colors);
	virtual ~Shape();
	virtual void draw()=0;
	virtual void save(std::ofstream &os)const=0;

	Point colors;
protected:
};



#endif /* _SHAPE_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

