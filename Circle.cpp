#include "Circle.h"

Circle::Circle()
	: Shape(),
		v1( Point(0,0,0) ),
		radius(0)
{
	//do nothing
}
Circle::Circle(const Point v1_in,
									const double radius_in,
									const Point colors_in)
	: Shape(colors_in),
		v1( v1_in ),
		radius( radius_in )
{
	//do nothing
}
std::istream & operator>>(std::istream &is, Circle &c){
	Point p; Point color; double r;
	is >> p.x >> p.y>>r >> color.x>>color.y>>color.z;
	c.v1 = p;
	c.colors = color;
	c.radius = r;
}
void Circle::save(std::ofstream &os)const{
	os << "Circle ";
	os << v1.x <<" "<< v1.y <<" ";
	os << radius <<" ";
	os << colors.x <<" "<<colors.y <<" "<<colors.z <<std::endl;
}
void Circle::draw(){
  glColor3d(colors.x,colors.y,colors.z);
	glBegin(GL_POLYGON);
  for(int i=0; i<32; i++)
    {
      double theta = (double)i/32.0 * 2.0 * 3.1415926;
      double x = v1.x + radius * cos(theta);
      double y = v1.y + radius * sin(theta);
      glVertex2d(x, y);
    }
  glEnd();
}
Circle::~Circle() {
	//do nothing
}
