#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

#include "texture.hpp"
#include "loader.hpp"

namespace Tetris {
  Texture::Texture(const char *texturePath) {
    _texture = loadBMP(texturePath);
    _name = texturePath;
  }

  Texture::~Texture() {
    glDeleteTextures(1, &this->_texture);
  }

  GLuint Texture::getTexture() {
    return this->_texture;
  }

  std::vector<Tetris::Texture *> getTextures(std::string dirpath) {
    std::vector<Tetris::Texture *> tet;

    for(const auto& p: std::filesystem::recursive_directory_iterator(dirpath)) {
      tet.push_back(new Tetris::Texture(p.path().u8string().c_str()));
    }
    return tet;
  }
}
