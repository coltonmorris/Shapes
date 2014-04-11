#include "Rectangle.h"

Rectangle::Rectangle()
	: Shape(),
		v1( Point(0,0,0) ),
		v2( Point(0,0,0) )
{
}
Rectangle::Rectangle(const Point v1_in,
									const Point v2_in,
									const Point colors_in)
	: Shape(colors_in),
		v1( v1_in ),
		v2( v2_in )
{
}
std::istream & operator>>(std::istream &is, Rectangle &r){
	Point p1; Point p2; Point color; 
	is>> p1.x >> p1.y
		>> p2.x >> p2.y
		>> color.x>>color.y>>color.z;
	r.v1 = p1;
	r.v2 = p2;
	r.colors = color;
}
void Rectangle::save(std::ofstream &os)const{
	os << "Rectangle ";
	os << v1.x <<" "<< v1.y <<" ";
	os << v2.x <<" "<< v2.y <<" ";
	os << colors.x <<" "<<colors.y <<" "<<colors.z <<std::endl;
}
void Rectangle::draw(){
	//declares color of shape
  glColor3d(colors.x,colors.y,colors.z);
  glBegin(GL_QUADS);
  glVertex2d(v1.x,v1.y);
  glVertex2d(v2.x,v1.y);
  glVertex2d(v2.x,v2.y);
  glVertex2d(v1.x,v2.y);
  glEnd();
}
Rectangle::~Rectangle() {
	//do nothing
}
