
#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Tetris {
  class Vertex  {
  public:
    // Vertex();
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
