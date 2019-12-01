
#pragma once

namespace Tetris {
  class Texture  {
  public:
    Texture(const char *texture);
    ~Texture();

    GLuint getTexture();
  private:
    GLuint _texture;
  };
}
