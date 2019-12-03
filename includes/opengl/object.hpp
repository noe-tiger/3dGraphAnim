
#pragma once

#include "texture.hpp"
#include "vertex.hpp"
#include "window.hpp"

namespace Tetris {
  class Cubi {
  public:
    Cubi(Tetris::Window &window,
	 Tetris::Vertex &vertex,
	 Tetris::Texture &texture,
	 bool full = true);
    ~Cubi();

    void setupPosition(glm::vec3 &orientation,
		       glm::vec3 &position,
		       glm::vec3 &scale,
		       glm::vec3 &lightPos);
    void draw();
    bool full();
    void setState(bool state);
    void disapear();
    Tetris::Cubi &operator=(const Tetris::Cubi &yes) {
      this->_window = yes._window;
      this->_vertex = yes._vertex;
      this->_texture = yes._texture;
      this->_full = yes._full;
      return *this;
    }
  private:
    
    glm::vec3 _orientation;
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _lightPos;

    Tetris::Window &_window;
    Tetris::Vertex &_vertex;
    Tetris::Texture &_texture;

    bool _full;
    double _scal;
  };

}
