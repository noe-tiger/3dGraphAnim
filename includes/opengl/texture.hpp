
#pragma once

#include <GLFW/glfw3.h>

namespace Tetris {
  class Texture  {
  public:
    Texture();
    Texture(const char *texture);
    ~Texture();

    GLuint getTexture();
  private:
    GLuint _texture;
  };
}
