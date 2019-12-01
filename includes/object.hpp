
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

#include "texture.hpp"
#include "vertex.hpp"
#include "window.hpp"

namespace Tetris {
  class Cubi {
  public:
    Cubi(Tetris::Window &window,
	 Tetris::Vertex &vertex,
	 Tetris::Texture &texture);
    ~Cubi();

    void setupPosition(glm::vec3 &orientation,
		       glm::vec3 &position,
		       glm::vec3 &scale,
		       glm::vec3 &lightPos);
    void draw();
    
  private:
    
    glm::vec3 _orientation;
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _lightPos;

    // size_t _objSize;
    // GLuint &_vertexbuffer;
    // GLuint &_uvbuffer;
    // GLuint &_normalbuffer;
    Tetris::Window &_window;
    Tetris::Vertex &_vertex;
    Tetris::Texture &_texture;
    
    // GLuint &_matrixID;
    // GLuint &_modelMatrixID;
    // GLuint &_viewMatrixID;
    // GLuint &_lightID;
    // GLuint &_textureID;
  };
}
