
#pragma once

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
    Tetris::Texture &getTexture();
    Tetris::Tetrimino &operator=(Tetris::Tetrimino &in) {
      this->_format = in._format;
      this->_str_format = in._str_format;
      this->_texture = in._texture;
      return *this;
    }
  private:
    std::vector<std::vector<char>> _format;
    std::string _str_format;
    Tetris::Texture _texture;
  };

  std::vector<Tetris::Tetrimino> getTetrimino(std::string dirpath);
}
