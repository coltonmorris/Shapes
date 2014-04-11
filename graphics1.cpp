
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>

#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Button.h"
#include "Slider.h"
#include "Point.h"

#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif


// Global Variables
double screen_x = 700;
double screen_y = 500;
std::vector<Shape *> Shapes;
std::vector<Button *> Buttons;
std::vector<Circle *> Clicks;
std::vector<Slider *> Sliders;
//circle=0,triangle=1,rectangle=2
int Mode = 0;
Button * Active;
Point activeLabel = Point(1,1,1);
Point deactiveLabel = Point(0,0,0);
Point activeColor;
std::ofstream fout;
std::ifstream fin;


void load(){
	fin.open("Shapes.txt");
	std::string keyword;
	while(fin>>keyword){
		if (keyword == "Circle"){
			Circle *c = new Circle();
			fin>>*c;
			Shapes.push_back(c);
		}
		else if (keyword == "Triangle"){
			Triangle *t = new Triangle();
			fin>>*t;
			Shapes.push_back(t);
		}
		else if (keyword == "Rectangle"){
			Rectangle *r = new Rectangle();
			fin>>*r;
			Shapes.push_back(r);
		}
	}
}
		

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
// basically the paint method
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
	
	//make sure active color is highlighted
	if (Active){
		Active->labelColor = activeLabel;
	}
	std::vector<Shape *>::const_iterator ptr;
	for (ptr = Shapes.begin();ptr != Shapes.end();ptr++){
		//ptr is a pointer to a pointer :D
		(*ptr)->draw();
	}

	if (!Clicks.empty()){
		std::vector<Circle *>::const_iterator cptr;
		for (cptr = Clicks.begin();cptr != Clicks.end();cptr++){
//			//cptr is a pointer to a pointer :D
				//std::cout<<(*cptr)->radius<<std::endl;
				(*cptr)->draw();
		}
	}

	std::vector<Button *>::const_iterator bptr;
	for (bptr = Buttons.begin();bptr != Buttons.end();bptr++){
		//bptr is a pointer to a pointer :D
		(*bptr)->draw();
	}
	std::vector<Slider *>::const_iterator sptr;
	for (sptr = Sliders.begin();sptr != Sliders.end();sptr++){
		//sptr is a pointer to a pointer :D
		(*sptr)->draw();
	}
  glutSwapBuffers();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
  switch (c) 
    {
    case 'q':
    case 27: // escape character means to quit the program
      exit(0);
      break;
    default:
      return; // if we don't care, return without glutPostRedisplay()
    }

  glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
  // Reset our global variables to the new width and height.
  screen_x = w;
  screen_y = h;

  // Set the pixel resolution of the final picture (Screen coordinates).
  glViewport(0, 0, w, h);

  // Set the projection mode to 2D orthographic, and set the world coordinates:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
  // translate pixel coordinates to display coordinates
  int xdisplay = x;
  int ydisplay = screen_y - y;
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
		}
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    {
		Point mouse = Point(xdisplay,ydisplay);
		//used to stop from registering the click if a button was clicked
		bool cont = true;
		//loop through sliders, if clicked on, change the buttons slider position
		std::vector<Slider *>::const_iterator sptr;
		for (sptr = Sliders.begin();sptr != Sliders.end();sptr++){
			if((*sptr)->contains(mouse)){
				cont = false;
				(*sptr)->setSlider(mouse);
				if((*sptr)->label == "Red"){
					activeColor.x = (*sptr)->getSliderValue();
				}
				else if((*sptr)->label == "Green"){
					activeColor.y = (*sptr)->getSliderValue();
				}
				else if((*sptr)->label == "Blue"){
					activeColor.z = (*sptr)->getSliderValue();
				}
			}
		}

//			//loop through buttons to see if click was in one of them
		std::vector<Button *>::const_iterator bptr;
		for (bptr = Buttons.begin();bptr != Buttons.end();bptr++){
			//default color for label is deactive color
			(*bptr)->labelColor=deactiveLabel;
			if ((*bptr)->contains(mouse)){
				//the click was inside the button, change color, Mode, Clicks
				cont = false;
				//make Active change and switch colors
				Active = *bptr;
				(*bptr)->labelColor = activeLabel;
				//clear clicks
				Clicks.clear();
				if((*bptr)->label == "Clear"){
					Active = 0;
					Clicks.clear();
					Shapes.clear();
				}
				else if((*bptr)->label == "Save"){
					Active = 0;
					Clicks.clear();

					fout.open("Shapes.txt"); // deletes previous content
					std::vector<Shape *>::const_iterator ptr;
					for (ptr = Shapes.begin();ptr != Shapes.end();ptr++){
						//ptr is a pointer to a pointer :D
						(*ptr)->save(fout);
					}
					fout.close();
				}
				else if((*bptr)->label == "Load"){
					Active = 0;
					Clicks.clear();

					load();
				}
				else if((*bptr)->label == "Quit"){
					exit(0);
				}
				else if((*bptr)->label == "Undo"){
					if (!Shapes.empty()){
					Active = 0;
					Clicks.clear();
					Shapes.pop_back();
					}
				}
				else if((*bptr)->label == "Circle"){
					Mode = 0;
				}
				else if((*bptr)->label == "Triangle"){
					Mode = 1;
				}
				else if((*bptr)->label == "Rectangle"){
					Mode = 2;
				}
			}			
		}
		if (cont && Active){
//					//active is a circle
				if (Mode == 0){
					//is it ready to draw?
					if (Clicks.size() == 1){
						//find radius
						Point vert = Clicks[0]->v1;
						double radius = sqrt(pow((mouse.x-vert.x),2)+pow((mouse.y-vert.y),2));
						//add object to Shapes
						Circle *circle = new Circle(vert,radius,activeColor);
						Shapes.push_back(circle);
						//clear clicks
						Clicks.clear();
					}
					//click is the vertex location
					else{
						Circle *c = new Circle(mouse,3,deactiveLabel);
						Clicks.push_back(c);
					}
				}
				if (Mode == 1){
					//is it ready to draw?
					if (Clicks.size() == 2){
						Point p1 = Clicks[0]->v1;
						Point p2 = Clicks[1]->v1;
						Triangle *triangle = new Triangle(p1,p2,mouse,activeColor);
						Shapes.push_back(triangle);
						Clicks.clear();
					}
					else{
						Circle *c = new Circle(mouse,3,deactiveLabel);
						Clicks.push_back(c);
					}
				}
				if (Mode == 2){
					//ready to draw?
					if (Clicks.size() == 1){
						Point p1 = Clicks[0]->v1;
						Rectangle *rect = new Rectangle(p1,mouse,activeColor);
						//this is giving a segmentation default??
						Shapes.push_back(rect);
						Clicks.clear();
					}
					else{
						Circle *c = new Circle(mouse,3,deactiveLabel);
						Clicks.push_back(c);
					}
				}
			}
		}
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
    {
    }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
    {
    }
  glutPostRedisplay();
}

void InitializeMyStuff()
{
	//create buttons
	Point colors = Point(.7,.7,.7);

	Point v1 = Point(10,10);
	Point v2 = Point(100,30);
	Button *quitBtn = new Button(v1,v2,colors,"Quit",deactiveLabel);

	v1=Point(10,40);
	v2=Point(100,60);
	Button *clearBtn= new Button(v1,v2,colors,"Clear",deactiveLabel);

	v1=Point(10,70);
	v2=Point(100,90);
	Button *circleBtn = new Button(v1,v2,colors,"Circle",activeLabel);

	v1=Point(10,100);
	v2=Point(100,120);
	Button *triangleBtn= new Button(v1,v2,colors,"Triangle",deactiveLabel);

	v1=Point(10,130);
	v2=Point(100,150);
	Button *rectangleBtn= new Button(v1,v2,colors,"Rectangle",deactiveLabel);

	v1=Point(10,160);
	v2=Point(100,180);
	Slider *blueBtn= new Slider(v1,v2,colors,"Blue",deactiveLabel,(Point(0,0,1)));

	v1=Point(10,190);
	v2=Point(100,210);
	Slider *greenBtn= new Slider(v1,v2,colors,"Green",deactiveLabel,(Point(0,1,0)));

	v1=Point(10,220);
	v2=Point(100,240);
	Slider *redBtn= new Slider(v1,v2,colors,"Red",deactiveLabel,(Point(1,0,0)));

	v1=Point(10,250);
	v2=Point(100,270);
	Button *undoBtn= new Button(v1,v2,colors,"Undo",deactiveLabel);

	v1=Point(10,280);
	v2=Point(100,300);
	Button *loadBtn= new Button(v1,v2,colors,"Load",deactiveLabel);

	v1=Point(10,310);
	v2=Point(100,330);
	Button *saveBtn= new Button(v1,v2,colors,"Save",deactiveLabel);

	Active = circleBtn;
	Buttons.push_back(quitBtn);
	Buttons.push_back(clearBtn);
	Buttons.push_back(circleBtn);
	Buttons.push_back(triangleBtn);
	Buttons.push_back(rectangleBtn);
	Buttons.push_back(undoBtn);
	Buttons.push_back(loadBtn);
	Buttons.push_back(saveBtn);
	Sliders.push_back(blueBtn);
	Sliders.push_back(greenBtn);
	Sliders.push_back(redBtn);


}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(screen_x, screen_y);
  glutInitWindowPosition(50, 50);

  int fullscreen = 0;
  if (fullscreen) 
    {
      glutGameModeString("800x600:32");
      glutEnterGameMode();
    } 
  else 
    {
      glutCreateWindow("Shapes by Colton Morris");
    }

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);

  glColor3d(0,0,0); // forground color
  glClearColor(1, 1, 1, 0); // background color
  InitializeMyStuff();

  glutMainLoop();

  return 0;
}

