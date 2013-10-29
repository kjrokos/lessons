#include <iostream>
#include <ncurses.h>

using namespace std;

int main()
{
  // declarations
  int key=0;

  int rows=0;
  int cols=0;

  // initialize ncurses
  initscr();

  // don't display the cursor
  curs_set(0);

  // don't display pressed keys on the screen
  noecho();

  // capture 'special' characters, like arrow keys
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS, NULL);

  // get the number of rows and columns
  getmaxyx(stdscr,rows,cols); 

  // initialize board (blank)
  bool **cells = new bool*[rows];
  bool **newcells = new bool*[rows];
  for(int r=0; r<rows; r++)
  {
    cells[r] = new bool[cols];
    newcells[r] = new bool[cols];
    for(int c=0; c<cols; c++)
    {
        cells[r][c] = false;
        newcells[r][c] = false;
    }
  }

  // determine initial configuration

  // wait up to 1000 ms for a keypress
  timeout(1000);

  while(key != 10)
  {
    // determine which key (if any) was pressed
    key = getch();

    // for each cell
    //  Rules:
    //   Any live cell with fewer than two live neighbours dies, as if caused by under-population.
    //   Any live cell with two or three live neighbours lives on to the next generation.
    //   Any live cell with more than three live neighbours dies, as if by overcrowding.
    //   Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

    // display 'O' at row r and column c
    // mvaddch(r,c,'O');

    // update the screen
    refresh();
  }

  endwin();

  // clean up afterwards
  for(int r=0; r<rows; r++)
  {
    delete[] cells[r];
    delete[] newcells[r];
  }
  delete[] cells;
  delete[] newcells;

  return 0;
}
