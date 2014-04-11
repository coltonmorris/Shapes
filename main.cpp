#include "Shape.h"
#include "Point.h"
#include <iostream>

int main(){
	Point p(1,2);
	Shape s(p);
	std::cout<<s.colors.z<<std::endl;
}
