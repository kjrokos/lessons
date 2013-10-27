#include <iostream>
#include <ncurses.h>
#include "gameOfLife.h"

using namespace std;

class GameOfLifeNcursesView {
  public:
    GameOfLifeNcursesView(GameOfLife &game);
    ~GameOfLifeNcursesView();

    void listen(int waitTime=-1);
    bool gotEnterKey(); 
    bool gotLeftMouseClick(int &row, int &col);

    void display();
  private:
    GameOfLife &m_game;
    int m_key;
};

  GameOfLifeNcursesView::GameOfLifeNcursesView(GameOfLife &game) 
: m_game(game),
  m_key(0)
{
  // initialize ncurses
  initscr();

  // don't display the cursor
  curs_set(0);

  // don't display pressed keys on the screen
  noecho();

  // capture 'special' characters, like arrow keys
  keypad(stdscr, TRUE);

  // capture mouse events
  mousemask(BUTTON1_CLICKED, NULL);

  // get the number of rows and columns
  int rows=0;
  int cols=0;
  getmaxyx(stdscr,rows,cols);

  game.resize(rows,cols);

  display();
};

GameOfLifeNcursesView::~GameOfLifeNcursesView()
{
  endwin();
}

void GameOfLifeNcursesView::listen(int waitTime)
{
  // wait up to 1000 ms for a keypress
  timeout(waitTime);

  m_key = getch();
}

bool GameOfLifeNcursesView::gotEnterKey()
{ 
  return m_key == 10; 
}

bool GameOfLifeNcursesView::gotLeftMouseClick(int &row, int &col)
{ 
  MEVENT event;

  if(m_key != KEY_MOUSE)
    return false;

  if(getmouse(&event) != OK)
    return false;

  if(event.bstate & BUTTON1_CLICKED)
  {
    row = event.y;
    col = event.x;
    return true;
  }

  return false;
}

void GameOfLifeNcursesView::display()
{
  for(int r=0; r<m_game.rows(); r++)
    for(int c=0; c<m_game.cols(); c++)
      if(m_game.cellAt(r,c)==true)
        mvaddch(r,c,'O');
      else
        mvaddch(r,c,' ');
  refresh();
}


int main()
{
  // create new game of life and view
  GameOfLife game;
  GameOfLifeNcursesView view(game);

  // determine initial configuration
  while(true)
  {
    // determine which key (if any) was pressed
    view.listen(1000);

    if(view.gotEnterKey())
      break;

    int r,c;
    if(view.gotLeftMouseClick(r,c))
    {
      game.flipCell(r,c);

      // display new configuration
      view.display();
    }
  }

  while(true)
  {
    // determine which key (if any) was pressed
    view.listen(1000);

    if(view.gotEnterKey())
      break;

    // get next iteration
    game.iterate();

    // display the board
    view.display();
  }

  return 0;
}
