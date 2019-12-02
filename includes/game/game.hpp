
#pragma once

#include "tetrimino.hpp"
#include "object.hpp"

namespace Tetris {
  // class Cubi {
  // public:
  //   Cubi() {
  //     _full = false;
  //   }
  //   ~Cubi() {}

  //   void draw() {}

  //   bool full() { // ADD CA DANS L AUTRE CUBI
  //     return _full;
  //   }

  //   void setState(bool state) { // ADD CA DANS L AUTRE CUBI
  //     _full = state;
  //   }

  //   void disapear() { // ADD FOR QUICK ANIMATION
  //     _full = false;
  //   }
  // private:
  //   bool _full;
  // };

  class Game {
  public:
    Game(int board_x, int board_y, std::vector<Tetris::Tetrimino> &tetriminos);
    ~Game();

    void print();
    void rotate(bool wise);
    void side(bool wise);
    bool update();

    std::vector<int> getFormat();
    const std::vector<std::vector<Tetris::Cubi>> &getBoard();
    const Tetris::Tetrimino &getFalling();
    const std::vector<std::vector<int>> &getFallingPos();
    const size_t getScore();
  private:
    bool getNext();
    bool canRotate(bool wise);
    void checkLine();

    std::vector<std::vector<Tetris::Cubi>> _gameBoard;
    std::vector<Tetris::Tetrimino> &_tetriminos;
    Tetris::Tetrimino _next;
    std::vector<std::vector<int>> _posNext;
    int _board_x, _board_y;
    size_t _score;
  };
}
