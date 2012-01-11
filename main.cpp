#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
using namespace std;

// function prototypes
void disp(void);
void keyb(unsigned char key, int x, int y);


// window identifier
static int win;

int main(int argc, char **argv){
 
  //////////
  // INIT //
  //////////

  // initialize glut
  glutInit(&argc, argv);

  // specify the display mode to be RGB and single buffering 
  // we use single buffering since this will be non animated
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

  // define the size
  glutInitWindowSize(500,500);

  // the position where the window will appear
  glutInitWindowPosition(100,100);
  

  // if we would want fullscreen:
  // glutFullScreen();

  // create the window, set the title and keep the 
  // window identifier.
  win = glutCreateWindow("Yet another teapot");

  //////////////
  // CALLBACK //
  //////////////

  glutDisplayFunc(disp);
  glutKeyboardFunc(keyb);
  
  ////////////
  // OPENGL //
  ////////////

  // define the color we use to clearscreen 
  glClearColor(0.0,0.0,0.0,0.0);



  // enter the main loop
  glutMainLoop();

  return 0;
}


void disp(void){

  // do  a clearscreen
  glClear(GL_COLOR_BUFFER_BIT);
  
  // draw something

  glutWireTeapot(0.5);
  // glutSolidTeapot(0.5);
  // glutWireSphere(0.5,100,100);
  // glutSolidSphere(0.5,100,100);
  // glutWireTorus(0.3,0.5,100,100);
  // glutSolidTorus(0.3,0.5,100,100);
  // glutWireIcosahedron();
  // glutSolidIcosahedron();
  // glutWireDodecahedron();
  // glutSolidDodecahedron();
  // glutWireCone(0.5,0.5,100,100);
  // glutSolidCone(0.5,0.5,100,100);
  // glutWireCube(0.5);
  // glutSolidCube(0.5);
}

void keyb(unsigned char key, int x, int y){
  cout << "Pressed key " << key << " on coordinates (" << x << "," << y << ")";
  cout << endl;
  if(key == 'q'){
    cout << "Got q,so quitting " << endl;
    glutDestroyWindow(win);
    exit(0);
  }
}
