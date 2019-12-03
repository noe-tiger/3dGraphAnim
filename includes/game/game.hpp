
#pragma once

#include "tetrimino.hpp"
#include "object.hpp"

#include "window.hpp"
#include "vertex.hpp"
#include "texture.hpp"

namespace Tetris {
  class Game {
  public:
    Game(int board_x, int board_y,
	 std::vector<Tetris::Tetrimino> &tetriminos,
	 Tetris::Window &window,
	 Tetris::Vertex &vertex,
	 Tetris::Texture &texture);
    ~Game();

    void print();
    void rotate(bool wise);
    void side(bool wise);
    bool update(std::vector<Tetris::Cubi *> &falling);

    std::vector<int> getFormat();
    const std::vector<std::vector<Tetris::Cubi *>> &getBoard();
    const Tetris::Tetrimino &getFalling();
    const std::vector<std::vector<int>> &getFallingPos();
    const size_t getScore();
  private:
    bool getNext();
    bool canRotate(bool wise);
    void checkLine();

    std::vector<std::vector<Tetris::Cubi *>> _gameBoard;
    std::vector<Tetris::Tetrimino> &_tetriminos;
    Tetris::Tetrimino _next;
    std::vector<std::vector<int>> _posNext;
    int _board_x, _board_y;
    size_t _score;

    Tetris::Window &_window;
    Tetris::Vertex &_vertex;
    Tetris::Texture &_texture;
  };
}
