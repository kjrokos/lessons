#include "gameOfLife.h"

GameOfLife::GameOfLife()
  :m_cells(0),
  m_newcells(0),
  m_rows(0),
  m_cols(0)
{
}

GameOfLife::GameOfLife(unsigned int rows, unsigned int cols)
  :m_cells(0),
  m_newcells(0),
  m_rows(0),
  m_cols(0)
{
  resize(rows,cols);
}

GameOfLife::~GameOfLife()
{
  resize(0,0);
}

bool GameOfLife::setCell(int row, int col, bool state)
{
  if(row>=0 && col>=0 && row<m_rows && col<m_cols)
  {
    m_cells[row][col] = state;
    return true;
  }

  return false;
}

bool GameOfLife::cellAt(int row, int col) const
{ 
  if(row>=0 && col>=0 && row<m_rows && col<m_cols)
    return m_cells[row][col]; 

  return false;
}

void GameOfLife::clear()
{
  for(int r=0; r<m_rows; r++)
    for(int c=0; c<m_cols; c++)
      setCell(r,c,false);
}

void GameOfLife::resize(unsigned int rows, unsigned int cols)
{
  if(m_rows != 0)
  {
    // if there is an existing board, delete it
    // before creating a new one
    for(int r=0; r<m_rows; r++)
    {
      delete[] m_cells[r];
      delete[] m_newcells[r];
    }
    delete[] m_cells;
    delete[] m_newcells;
  }

  m_rows = rows;
  m_cols = cols;

  if(rows != 0)
  {
    // initialize new board (blank)
    m_cells = new bool*[rows];
    m_newcells = new bool*[rows];
    for(int r=0; r<rows; r++)
    {
      m_cells[r] = new bool[cols];
      m_newcells[r] = new bool[cols];
      for(int c=0; c<cols; c++)
      {
        m_cells[r][c] = false;
        m_newcells[r][c] = false;
      }
    }
  }
}

void GameOfLife::iterate()
{
  // for each cell
  for(int r=0; r<m_rows; r++)
  {
    for(int c=0; c<m_cols; c++)
    {
      // find number of alive neighbors
      int numAlive=0;
      for(int i=r-1; i<=r+1; i++)
        for(int j=c-1; j<=c+1; j++)
          if(!(i==r && j==c))
            if(cellAt(i,j))
              numAlive++;

      m_newcells[r][c]=false;

      //  Rules:
      //   Any live cell with fewer than two live neighbours dies, as if caused by under-population.
      if (numAlive<2)
        m_newcells[r][c]=false;

      //   Any live cell with two or three live neighbours lives on to the next generation.
      if (numAlive>=2 && numAlive<=3 && m_cells[r][c]==true)
        m_newcells[r][c]=true;

      //   Any live cell with more than three live neighbours dies, as if by overcrowding.
      if (numAlive>3)
        m_newcells[r][c]=false;

      //   Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
      if (numAlive==3 && m_cells[r][c]==false)
        m_newcells[r][c]=true;
    }
  }

  // now that we've computed the next state for
  // the game, set the cells to their new values
  for(int r=0; r<m_rows; r++)
    for(int c=0; c<m_cols; c++)
      setCell(r,c, m_newcells[r][c]);
}

