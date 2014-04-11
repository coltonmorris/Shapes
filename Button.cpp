#include "Button.h"
#include <iostream>

Button::Button()
	: Rectangle(),
		label(0),
		labelColor(Point(0,0,0))
{
}
Button::Button(const Point v1_in,
									const Point v2_in,
									const Point colors_in,
									const char *label_in,
									const Point labelColor_in)
	: Rectangle(v1_in,v2_in,colors_in),
		label(label_in),
		labelColor(labelColor_in)
{
}
void Button::draw(){
	//draw rectangle
  glColor3d(colors.x,colors.y,colors.z);
  glBegin(GL_QUADS);
  glVertex2d(v1.x,v1.y);
  glVertex2d(v2.x,v1.y);
  glVertex2d(v2.x,v2.y);
  glVertex2d(v1.x,v2.y);
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
bool Button::contains(const Point p_in){
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
Button::~Button() {
	//do nothing
}

