
#pragma once

#include <iostream>
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "texture.hpp

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
