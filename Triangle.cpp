#include "Triangle.h"

Triangle::Triangle()
	: Shape(),
		v1( Point(0,0,0) ),
		v2( Point(0,0,0) ),
		v3( Point(0,0,0) )
{
}
Triangle::Triangle(const Point v1_in,
									const Point v2_in,
									const Point v3_in,
									const Point colors_in)
	: Shape(colors_in),
		v1( v1_in ),
		v2( v2_in ),
		v3( v3_in )
{
}
std::istream & operator>>(std::istream &is, Triangle &t){
	Point p1; Point p2; Point p3; Point color; 
	is>> p1.x >> p1.y
		>> p2.x >> p2.y
		>> p3.x >> p3.y
		>> color.x>>color.y>>color.z;
	t.v1 = p1;
	t.v2 = p2;
	t.v3 = p3;
	t.colors = color;
}
void Triangle::save(std::ofstream &os)const{
	os << "Triangle ";
	os << v1.x <<" "<< v1.y <<" ";
	os << v2.x <<" "<< v2.y <<" ";
	os << v3.x <<" "<< v3.y <<" ";
	os << colors.x <<" "<<colors.y <<" "<<colors.z <<std::endl;
}
void Triangle::draw(){
  glColor3d(colors.x,colors.y,colors.z);
	glBegin(GL_TRIANGLES);
  glVertex2d(v1.x,v1.y);
	glVertex2d(v2.x,v2.y);
	glVertex2d(v3.x,v3.y);
	glEnd();
}
Triangle::~Triangle() {
	//do nothing
}
