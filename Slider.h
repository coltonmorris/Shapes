#ifndef _SLIDER_H_
#define _SLIDER_H_

#include "Button.h"
#include <cstring>

class Slider : public Button
{
public:
	Slider();
	Slider(const Point v1_in,const Point v2_in,const Point colors_in,const char * label_in,
					const Point labelColor_in,const Point sliderColor_in);
	virtual ~Slider();
	void setSlider(Point vert);
	const double getSliderValue();
	//get this inheritance to work,yo
	bool contains(const Point p_in);
	virtual void draw();

	Rectangle slider;
	Point sliderColor;
protected:
};


#endif /* _SLIDER_H_ */
/* Local Variables: */
/* mode:c++ 				*/
/* End: 						*/

