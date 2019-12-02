
#pragma once

#include <string>

namespace Tetris {
  class Tetrimino {
  public:
    Tetrimino();
    Tetrimino(const char *format);

    ~Tetrimino();

    void rotateRight();
    void rotateLeft();
    
    void print();
    std::vector<std::vector<char>> getFormat();
  private:
    std::vector<std::vector<char>> _format;
    std::string _str_format;
  };

  std::vector<Tetris::Tetrimino> getTetrimino(std::string dirpath);
}
