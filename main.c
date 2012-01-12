#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <GL/glut.h>
#include "glm.h"

GLuint     model_list = 0;		/* display list for object */
char*      model_file = NULL;		/* name of the obect file */
GLboolean  facet_normal = GL_FALSE;	/* draw with facet normal? */
GLMmodel*  model;
GLfloat    smoothing_angle = 90.0;	/* smoothing angle */
GLfloat    scale;			
GLdouble   pan_x = 0.0;
GLdouble   pan_y = 0.0;
GLdouble   pan_z = 0.0;
float      pan_amount = 0.5;
float      angle = 0.0;
float      angle_step = 15.0;


void lists(void) {
  if (model_list) glDeleteLists(model_list, 1);

  model_list = glmList(model, GLM_SMOOTH);
}

void
init(void)
{
  
  /* read in the model */
  model = glmReadOBJ(model_file);
  scale = glmUnitize(model);
  glmFacetNormals(model);
  glmVertexNormals(model, smoothing_angle);

  /* create new display lists */
  lists();

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -2.0);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  glTranslatef(pan_x, pan_y, 0.0);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);


  glEnable(GL_LIGHTING);
  glColor3f(0.5, 0.5, 0.5);
  glCallList(model_list);

  glPopMatrix();

  glutSwapBuffers();
}

void
keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'w':
    pan_y -= pan_amount;
    break;

  case 'd':
    pan_x += pan_amount;
    break;

  case 'a':
    pan_x -= pan_amount;
    break;

  case 's':
    pan_y += pan_amount;
    break;

  case 't':
    glmScale(model, 0.8);
    lists();
    break;

  case 'z':
    angle -= 15;
    break;

  case 'x':
    angle += 15.0;
    break;

  case 'g':
    glmScale(model, 1.25);
    lists();
    break;

  case 'q':
  case 27:
    exit(0);
    break;
  }

  glutPostRedisplay();
}

int
main(int argc, char** argv)
{
  glutInitWindowSize(1024, 1024);
  glutInit(&argc, argv);

  model_file = argv[1];
  if (!model_file) {
    fprintf(stderr, "usage: smooth model_file.obj\n");
    exit(1);
  }

  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("wiatrak");
  
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  
  init();
  
  glutMainLoop();
  return 0;
}
