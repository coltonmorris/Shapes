#include "Shape.h"
#include "Point.h"
#include <iostream>

Shape::Shape(){
	this->colors = Point(0,0,0);
}
Shape::Shape(const Point colors_in){
	this->colors = colors_in;
}
Shape::~Shape() {
	//do nothing
}
