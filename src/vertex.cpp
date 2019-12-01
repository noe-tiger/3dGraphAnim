
#include "vertex.hpp"
#include "loader.hpp"

namespace Tetris {
  Vertex::Vertex(const char *filename) {
    loadOBJ("../sources/suzanne.obj", this->_vertices, this->_uvs, this->_normals);

    glGenBuffers(1, &this->_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(glm::vec3), &this->_vertices[0], GL_STATIC_DRAW);
    glGenBuffers(1, &this->_uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->_uvs.size() * sizeof(glm::vec2), &this->_uvs[0], GL_STATIC_DRAW);
    glGenBuffers(1, &this->_normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->_normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->_normals.size() * sizeof(glm::vec3), &this->_normals[0], GL_STATIC_DRAW);
  }

  Vertex::~Vertex() {
    glDeleteBuffers(1, &this->_vertexbuffer);
    glDeleteBuffers(1, &this->_uvbuffer);
    glDeleteBuffers(1, &this->_normalbuffer);
  }

  std::vector<glm::vec3> &Vertex::getVertices() {
    return this->_vertices;
  }

  std::vector<glm::vec2> &Vertex::getUvs() {
    return this->_uvs;
  }

  std::vector<glm::vec3> &Vertex::getNormals() {
    return this->_normals;
  }

  GLuint Vertex::getVertexBuffer() {
    return this->_vertexbuffer;
  }

  GLuint Vertex::getUvBuffer() {
    return this->_uvbuffer;
  }

  GLuint Vertex::getNormalBuffer() {
    return this->_normalbuffer;
  }
}
