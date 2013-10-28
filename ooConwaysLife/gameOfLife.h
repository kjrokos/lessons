#ifndef __GAME_OF_LIFE_H__
#define __GAME_OF_LIFE_H__

class GameOfLife {
  public:
    GameOfLife();
    GameOfLife(unsigned int rows, unsigned int cols);
    ~GameOfLife();

    void iterate();

    int rows() const { return m_rows; };
    int cols() const { return m_cols; };

    bool cellAt(int row, int col) const;
    bool setCell(int row, int col, bool state);
    void flipCell(int row, int col) { setCell(row,col,!cellAt(row,col)); }

    void clear();

    void resize(unsigned int rows, unsigned int cols);

  private:
    bool **m_cells;
    bool **m_newcells;

    unsigned int m_rows;
    unsigned int m_cols;
};

#endif
