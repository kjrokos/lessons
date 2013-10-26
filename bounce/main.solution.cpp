#include <iostream>
#include <ncurses.h>

using namespace std;

class Ball
{
  public:
  Ball(float x, float y, float dx, float dy)
    : m_x(x),
      m_y(y),
      m_dx(dx),
      m_dy(dy) {}

  float getX() { return m_x; }
  float getY() { return m_y; }

  void increment_dx() {m_dx += 0.1;}
  void decrement_dx() {m_dx -= 0.1;}

  void increment_dy() {m_dy += 0.1;}
  void decrement_dy() {m_dy -= 0.1;}

  void computeNextPosition(float maxX, float maxY);
  
  private:

  float m_x;
  float m_y;
  float m_dx;
  float m_dy;
};

void Ball::computeNextPosition(float maxX, float maxY)
{
  m_x += m_dx;
  m_y += m_dy;

  // if the ball hits a wall, reverse the
  // velocity ('bounce') and recompute
  // position
  if(m_x <= 0 && m_dx < 0)
  {
    m_dx = -m_dx;
    m_x = -m_x;
  }
  if(m_x > maxX && m_dx > 0)
  {
    m_dx = -m_dx;
    m_x = maxX - (m_x-maxX);
  }
  if(m_y <= 0 && m_dy < 0)
  {
    m_dy = -m_dy;
    m_y = -m_y;
  }
  if(m_y > maxY && m_dy > 0)
  {
    m_dy = -m_dy;
    m_y = maxY - (m_y-maxY);
  }
}

int main()
{
  // declarations
  int key=0;

  Ball ball(0,0,0,0);

  int maxY=0;
  int maxX=0;

  // initialize ncurses
  initscr();

  // don't display the cursor
  curs_set(0);

  // don't display pressed keys on the screen
  noecho();

  // capture 'special' characters, like arrow keys
  keypad(stdscr, TRUE);

  // print initial ball
  mvaddch(ball.getY(),ball.getX(),'O');

  // wait 10ms for a keypress
  timeout(10);


  while(key != 10)
  {
    // determine which key (if any) was pressed
    key = getch();

    // figure out what to do with the keypress
    switch(key)
    {
      case KEY_LEFT:
        ball.decrement_dx();
        break;

      case KEY_RIGHT:
        ball.increment_dx();
        break;

      case KEY_UP:
        ball.decrement_dy();
        break;

      case KEY_DOWN:
        ball.increment_dy();
        break;

      default: 
        // do nothing if a key other
        // than an arrow key was pressed,
        // or no key was pressed
        break;
    }

    // erase (by writing a space over the 'O')
    // the position where the ball was last
    mvaddch((int)ball.getY(),(int)ball.getX(),' ');

    // get the number of rows and columns
    getmaxyx(stdscr,maxY,maxX); 

    // compute the new position of the ball
    ball.computeNextPosition(maxX, maxY);

    // write the ball in the new position
    mvaddch((int)ball.getY(),(int)ball.getX(),'O');

    // update the screen
    refresh();
  }

  endwin();
  return 0;
}
