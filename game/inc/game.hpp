
#pragma once

#include "tetrimino.hpp"

namespace Tetris {
  class Cubi {
  public:
    Cubi() {
      _full = false;
    }
    ~Cubi() {}

    void draw() {}

    bool full() { // ADD CA DANS L AUTRE CUBI
      return _full;
    }

    void setState(bool state) { // ADD CA DANS L AUTRE CUBI
      _full = state;
    }
  private:
    bool _full;
  };

  class Game {
  public:
    Game(int board_x, int board_y, std::vector<Tetris::Tetrimino> &tetriminos);
    ~Game();

    void print();
    void rotate(bool wise);
    void side(bool wise);
    bool update();
  private:
    Tetris::Tetrimino getNext();

    std::vector<std::vector<Tetris::Cubi>> _gameBoard;
    std::vector<Tetris::Tetrimino> &_tetriminos;
    Tetris::Tetrimino _next;
    std::vector<std::vector<int>> _posNext;
    int _board_x, _board_y;
  };
}
