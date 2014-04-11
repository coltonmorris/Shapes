#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Rectangle.h"
#include <cstring>

class Button : public Rectangle
{
public:
	Button();
	Button(const Point v1_in,const Point v2_in,const Point colors_in,const char * label_in,
					const Point labelColor_in);
	virtual ~Button();
	virtual void draw();
	bool contains(const Point p_in);

	const char * label;
	Point labelColor;
protected:
};


#endif /* _BUTTON_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

