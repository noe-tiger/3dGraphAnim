
#pragma once

#include <vector>

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
    bool update(std::vector<Tetris::Cubi *> &falling, bool &update);

    std::vector<int> getFormat();
    const std::vector<std::vector<Tetris::Cubi *>> &getBoard();
    const Tetris::Tetrimino &getFalling();
    const std::vector<std::vector<int>> &getFallingPos();
    const std::vector<std::vector<int>> getFallingPos(Tetris::Tetrimino, int x, int y);
    const size_t getScore();
    const size_t getTetID();
  private:
    bool getNext();
    bool canRotate(bool wise);
    void checkLine(std::vector<int> &anim);

    std::vector<std::vector<Tetris::Cubi *>> _gameBoard;
    std::vector<Tetris::Tetrimino> &_tetriminos;
    Tetris::Tetrimino _next;
    std::vector<std::vector<int>> _posNext;
    int _board_x, _board_y;
    size_t _score;
    size_t _id;

    Tetris::Window &_window;
    Tetris::Vertex &_vertex;
    Tetris::Texture &_texture;
  };
}
