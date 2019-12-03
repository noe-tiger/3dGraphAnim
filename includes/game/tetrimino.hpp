
#pragma once

#include <string>

#include "object.hpp"

namespace Tetris {
  class Tetrimino {
  public:
    Tetrimino(const char *format,
	      const char *texture,
	      const char *vertex,
	      Tetris::Window &window);

    ~Tetrimino();

    void rotateRight();
    void rotateLeft();
    
    void print();
    std::vector<std::vector<char>> getFormat();
    std::vector<Tetris::Cubi> &getBlock();

    Tetris::Tetrimino &operator=(Tetris::Tetrimino &in) {
      return in;
    }
  private:
    std::vector<Tetris::Cubi> _block;
    std::vector<std::vector<char>> _format;
    std::string _str_format;
    Tetris::Window &_window;
  };

  std::vector<Tetris::Tetrimino> getTetrimino(std::string dirpath, Tetris::Window &window, const char *objpath);
}
