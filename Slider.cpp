#include "Slider.h"
#include <iostream>

Slider::Slider()
	: Button(),
		slider()
{
}
Slider::Slider(const Point v1_in,
									const Point v2_in,
									const Point colors_in,
									const char *label_in,
									const Point labelColor_in,
									const Point sliderColor_in)
	: Button(v1_in,v2_in,colors_in,label_in,labelColor_in),
		slider((Point(v1_in.x,v1_in.y)),(Point(v1_in.x+10,v1_in.y+20)),sliderColor_in)
{
}
void Slider::draw(){
	//draw rectangle
  glColor3d(colors.x,colors.y,colors.z);
  glBegin(GL_QUADS);
  glVertex2d(v1.x,v1.y);
  glVertex2d(v2.x,v1.y);
  glVertex2d(v2.x,v2.y);
  glVertex2d(v1.x,v2.y);
  glEnd();
	//draw slider, default color is black
  glColor3d(slider.colors.x,slider.colors.y,slider.colors.z);
  glBegin(GL_QUADS);
  glVertex2d(slider.v1.x,slider.v1.y);
  glVertex2d(slider.v2.x,slider.v1.y);
  glVertex2d(slider.v2.x,slider.v2.y);
  glVertex2d(slider.v1.x,slider.v2.y);
  glEnd();
	//draw text
  glColor3d(labelColor.x,labelColor.y,labelColor.z);
  void *font = GLUT_BITMAP_9_BY_15;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
	
  int len, i;
	double x= v1.x+5;
	double y= v1.y+5;
  glRasterPos2d(x, y);
  len = (int) strlen(label);
  for (i = 0; i < len; i++) 
    {
      glutBitmapCharacter(font, label[i]);
    }
  glDisable(GL_BLEND);
}
void Slider::setSlider(Point vert){
	slider.v1.x=vert.x-5;
	slider.v2.x=vert.x+5;
}
const double Slider::getSliderValue(){
	double slider_x = slider.v1.x+5;
	double button_x1 = v1.x;
	double button_x2 = v2.x;
	double value = (1*(slider_x-button_x1))/(button_x2-button_x1);
	return value;
}
bool Slider::contains(const Point p_in){
	//point is less than x
	if ((p_in.x < v1.x) && (p_in.x < v2.x)){
		return false;
	}
	//point is greater than x
	else if ((p_in.x > v1.x) && (p_in.x > v2.x)){
		return false;
	}
	//point is less than y
	else if ((p_in.y < v1.y) && (p_in.y < v2.y)){
		return false;
	}
	//point is greater than y
	else if ((p_in.y > v1.y) && (p_in.y > v2.y)){
		return false;
	}
	else{
		return true;
	}
}
Slider::~Slider() {
	//do nothing
}

