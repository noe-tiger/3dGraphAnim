#include <iostream>
#include <vector>

#include "tetrimino.hpp"
#include "game.hpp"

int main() {
  std::vector<Tetris::Tetrimino> tet = Tetris::getTetrimino("./tetrimino");
  Tetris::Game game(10, 21, tet);
  // game.rotate(true);
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.side(true);
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  // game.update();
  while (game.update());
  game.print();
  return 0;
}
