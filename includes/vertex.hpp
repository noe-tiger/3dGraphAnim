
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

namespace Tetris {
  class Vertex  {
  public:
    Vertex(const char *filename);
    ~Vertex();

    std::vector<glm::vec3> &getVertices();
    std::vector<glm::vec2> &getUvs();
    std::vector<glm::vec3> &getNormals();
    GLuint getVertexBuffer();
    GLuint getUvBuffer();
    GLuint getNormalBuffer();
  private:
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec2> _uvs;
    std::vector<glm::vec3> _normals;
    GLuint _vertexbuffer;
    GLuint _uvbuffer;
    GLuint _normalbuffer;
  };
}
