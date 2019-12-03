#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "texture.hpp"
#include "loader.hpp"

namespace Tetris {
  Texture::Texture(const char *texturePath) {
    _texture = loadBMP(texturePath);
  }

  Texture::~Texture() {
    glDeleteTextures(1, &this->_texture);
  }

  GLuint Texture::getTexture() {
    return this->_texture;
  }
}
