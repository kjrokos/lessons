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
  while(key != 10)
  {
    // determine which key (if any) was pressed
    key = getch();

    MEVENT event;

    if(key == KEY_MOUSE)
    {
      if(getmouse(&event)==OK)
      {
        if(event.bstate & BUTTON1_CLICKED)
        {
          cells[event.y][event.x] = !cells[event.y][event.x];

          // display current configuration
          for(int r=0; r<rows; r++)
            for(int c=0; c<cols; c++)
              if(cells[r][c]==true)
                mvaddch(r,c,'O');
              else
                mvaddch(r,c,' ');

          refresh();
        }
      }
    }
  }
  key = 0;

  // wait up to 1000 ms for a keypress
  timeout(1000);

  while(key != 10)
  {
    // determine which key (if any) was pressed
    key = getch();

    for(int r=0; r<rows; r++)
    {
      for(int c=0; c<cols; c++)
      {
        int numAlive=0;
        for(int i=r-1; i<=r+1; i++)
          for(int j=c-1; j<=c+1; j++)
            if(i>=0 && j>=0 && i<rows && j<cols)
              if(!(i==r && j==c))
                if(cells[i][j])
                  numAlive++;

        // for each cell
        //  Rules:
        //   Any live cell with fewer than two live neighbours dies, as if caused by under-population.
        if (numAlive<2)
          newcells[r][c]=false;

        //   Any live cell with two or three live neighbours lives on to the next generation.
        if (numAlive>=2 && numAlive<=3 && cells[r][c]==true)
          newcells[r][c]=true;

        //   Any live cell with more than three live neighbours dies, as if by overcrowding.
        if (numAlive>3)
          newcells[r][c]=false;

        //   Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        if (numAlive==3 && cells[r][c]==false)
          newcells[r][c]=true;
      }
    }

    // now that we've computed the next state for
    // the game, set the cells to their new values
    for(int r=0; r<rows; r++)
    {
      for(int c=0; c<cols; c++)
      {
        cells[r][c] = newcells[r][c];
        newcells[r][c]=false;
      }
    }

    // display the board
    for(int r=0; r<rows; r++)
      for(int c=0; c<cols; c++)
        if(cells[r][c]==true)
          mvaddch(r,c,'O');
        else
          mvaddch(r,c,' ');

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
