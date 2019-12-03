
#pragma once

#include <vector>
#include <string>

#include "object.hpp"

namespace Tetris {
  class Tetrimino {
  public:
    Tetrimino(const char *format,
	      const char *texture);

    ~Tetrimino();

    void rotateRight();
    void rotateLeft();

    void print();
    std::vector<std::vector<char>> getFormat();
    Tetris::Tetrimino &operator=(Tetris::Tetrimino &in) {
      this->_format = in._format;
      this->_str_format = in._str_format;
      return *this;
    }
  private:
    std::vector<std::vector<char>> _format;
    std::string _str_format;
  };

  std::vector<Tetris::Tetrimino> getTetrimino(std::string dirpath);
}
