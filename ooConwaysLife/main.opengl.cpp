#include <cstdlib>
#include <iostream>
#include <GLUT/glut.h>
#include "gameOfLife.h"


static GameOfLife *s_game = 0;
static bool s_placementMode = true;
static int s_placing = 2;

void mouseEvent(int button, int state, int x, int y)
{
  if(s_placementMode == true && s_game != NULL)
  {
    if(button == GLUT_LEFT_BUTTON)
    {
      if(state == GLUT_DOWN)
      {
        s_game->flipCell(y/5, x/5);
        s_placing = (int) s_game->cellAt(y/5, x/5);
      }
      if(state == GLUT_UP)
      {
        s_placing = 2;
      }
    }
  }
}

void mouseMove(int x, int y)
{
  if(s_placing<2)
    s_game->setCell(y/5, x/5, (bool)s_placing);
}

void iteratorFunc(int)
{
  s_game->iterate();
  if(s_placementMode==false)
    glutTimerFunc(100, iteratorFunc, 0);
  glutPostRedisplay();
}

void keyboardEvent(unsigned char key, int x, int y)
{
  if(key == ' ' && s_placementMode==true)
  {
    std::cout << "Running Life!" << std::endl;
    glutTimerFunc(100, iteratorFunc, 0);
    s_placementMode=false;
  }
  else if(key == ' ' && s_placementMode==false)
  {
    std::cout << "Beginning placement mode" << std::endl;
    s_placementMode=true;
  }
  else if(key == 'c')
  {
    std::cout << "clearing game; beginning placement mode" << std::endl;
    s_placementMode=true;
    s_game->clear();
  }
  else if(key == 'q')
  {
    std::cout << "exiting" << std::endl;
    exit(0);
  }
}

void display() {

  //clear white, draw with black
  glClearColor(255, 255, 255, 0);
  glColor3d(0, 0, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(s_game != 0)
  {
    for(int r=0; r<s_game->rows(); r++)
      for(int c=0; c<s_game->cols(); c++)
        if(s_game->cellAt(r,c)==true)
          glRecti(c*5,r*5, (c+1)*5, (r+1)*5);
  }

  glutSwapBuffers();
}

void reshape(int width, int height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set the coordinate system, with the origin in the top left
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {

    glutPostRedisplay();
}

void startOGL(int argc, char **argv, GameOfLife &game)
{
  s_game = &game;

  //a basic set up...
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(640, 480);

  s_game->resize(480/5, 640/5);
  std::cout << "Resized to: " << s_game->rows() << " rows and: " << s_game->cols() << " cols" << std::endl;

  //create the window, the argument is the title
  glutCreateWindow("Conway's game of Life");

  //pass the callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMouseFunc(mouseEvent);
  glutMotionFunc(mouseMove);
  glutKeyboardFunc(keyboardEvent);

  glutMainLoop();
}

int main(int argc, char **argv) {

  //create new game of life and view
  GameOfLife game;
  startOGL(argc, argv, game);

  return 0;
}
