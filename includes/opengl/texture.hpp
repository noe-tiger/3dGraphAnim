
#pragma once

#include <iostream>

#include <GLFW/glfw3.h>

namespace Tetris {
  class Texture  {
  public:
    // Texture();
    Texture(const char *texture);
    ~Texture();

    GLuint getTexture();
    void print() {
      std::cout << _texture << "\t" << _name << std::endl;
    }
  private:
    GLuint _texture;
    std::string _name;
  };
}
