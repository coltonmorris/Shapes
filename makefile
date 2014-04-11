LDFLAGS := -lglut -lGLU -lGL
run: Slider.o Button.o Shape.o Point.o Triangle.o Circle.o Rectangle.o graphics1.o
	g++ -o run Slider.o Button.o Shape.o Point.o Triangle.o Circle.o Rectangle.o graphics1.o $(LDFLAGS)
main.o: main.cpp
	g++ -c main.cpp
Slider.o: Slider.cpp Slider.h
	g++ -c Slider.cpp 
Button.o: Button.cpp Button.h
	g++ -c Button.cpp 
Rectangle.o: Rectangle.cpp Rectangle.h
	g++ -c Rectangle.cpp 
Circle.o: Circle.cpp Circle.h
	g++ -c Circle.cpp 
Triangle.o: Triangle.cpp Triangle.h
	g++ -c Triangle.cpp
Point.o: Point.cpp Point.h
	g++ -c Point.cpp
Shape.o: Shape.cpp Shape.h
	g++ -c Shape.cpp
graphics1.o: graphics1.cpp
	g++ -c graphics1.cpp
clean:
	rm -r *.o
	rm -rf *~
