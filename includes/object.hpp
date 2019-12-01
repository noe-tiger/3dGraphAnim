
#pragma once

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

    Tetris::Window &_window;
    Tetris::Vertex &_vertex;
    Tetris::Texture &_texture;
  };
}
