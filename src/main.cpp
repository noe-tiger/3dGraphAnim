#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "controls.hpp"
#include "object.hpp"
#include "window.hpp"
#include "texture.hpp"
#include "vertex.hpp"

#include "game.hpp"

void showBoardEdge(std::vector<Tetris::Cubi> &boardEdge, int x, int y) {
  glm::vec3 scale(1.0, 1.0, 1.0);
  glm::vec3 orientation(0.0, 0.0, 0.0);
  for (int i = 0; i < boardEdge.size(); i += 1) {
    glm::vec3 position(0, 0, -(x > y ? x : y) * 3);
    glm::vec3 light(4, 4, -(x > y ? x : y) * 3 + 4);

    if (i < y * 2) {
      position.y = y - (i % 2 ? i : i + 1);
      light.y = y - (i % 2 ? i : i + 1) + 4;
      position.x = (i % 2 ? x : -x - 2);
      light.x = (i % 2 ? x : -x - 2) + 4;
    } else {
      position.x = (x) - (i - 2 * y) * 2;
      light.x = (x) - (i - 2 * y) * 2 + 4;
      position.y = -y - 1;
      light.y = -y - 1 + 4;
    }
    boardEdge[i].setupPosition(orientation, position, scale, light);
    boardEdge[i].draw();
  }
}

void showBoard(Tetris::Game &game, std::vector<Tetris::Cubi *> &falling) {
  int x = game.getFormat()[0];
  int y = game.getFormat()[1];
  glm::vec3 orientation(0.0, 0.0, 0.0);
  glm::vec3 pos(0.0, 0.0, -(x > y ? x : y) * 3);
  glm::vec3 scale(1.0, 1.0, 1.0);
  glm::vec3 light(4, 4, -(x > y ? x : y) * 3 + 4);
  std::vector<std::vector<Tetris::Cubi *>> board = game.getBoard();
  for (int i = 0; i < board.size(); i += 1) {
    for (int j = 0; j < board[i].size(); j += 1) {
      pos.y = y - 1 - i * 2;
      pos.x = -x + j * 2;
      light.y =  y - 1 - i * 2 + 4;
      light.x =  -x + j * 2 + 4;
      board[i][j]->setupPosition(orientation, pos, scale, light);
      board[i][j]->draw();
    }
  }

  pos.z += 1;
  std::vector<std::vector<int>> position = game.getFallingPos();
  for (int i = 0; i < falling.size() && i < position.size(); i += 1) {
    pos.y = y - 1 - position[i][1] * 2;
    pos.x = -x + position[i][0] * 2;
    light.y = y - 1 - position[i][1] * 2 + 4;
    light.x = -x + position[i][0] * 2 + 4;
    falling[i]->setupPosition(orientation, pos, scale, light);
    falling[i]->draw();
}
}

int main()
{
  // create window, basic models and textures
  Tetris::Window window("../sources/shader/vertex.glsm", "../sources/shader/shader.glsm");
  Tetris::Texture edgeTexture("../sources/edge_texture.bmp");
  Tetris::Vertex edgeVertex("../sources/block.obj");
  Tetris::Vertex boardVertex("../sources/block.obj");

  // create board out of theses dimensions
  int y = 21;
  int x = 10;
  // get all tetriminos
  std::vector<Tetris::Tetrimino> tet = Tetris::getTetrimino("../sources/tetrimino_file");
  // get all texture for the tetriminos /!\ they need to have the same name
  std::vector<Tetris::Texture *> textures = Tetris::getTextures("../sources/tetrimino_texture");
  // create game object
  Tetris::Game game(x, y, tet, window, boardVertex, edgeTexture);

  // create edge object to render
  std::vector<Tetris::Cubi> boardEdge;
  for (int i = 0; i < (x + 2 + (2 * y)); i += 1) {
    Tetris::Cubi object(window, edgeVertex, edgeTexture);
    boardEdge.push_back(object);
  }

  // create falling object to render
  std::vector<Tetris::Cubi *> falling;
  for (int i = 0; i < game.getFallingPos().size(); i += 1) {
    falling.push_back(new Tetris::Cubi(window, boardVertex, *textures[game.getTetID()]));
  }

  // init clock
  double lastTime = glfwGetTime();
  double timeout = 0.0f;
  do{
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    bool update = false;
    lastTime = currentTime;
    timeout += deltaTime;

    // update the game at timeout
    if (timeout > (1 - 0.01 * game.getScore())) {
      bool ret = game.update(falling, update);
      if (!ret)
      	break ;
      timeout = 0;
    }

    // update window
    window.clearScreen();
    inputs(window.getWindow(), game, falling, update);
    showBoardEdge(boardEdge, x, y);
    showBoard(game, falling);

    // change the falling object
  //   if (update) {
  //     falling.clear();
  //     for (int i = 0; i < game.getFallingPos().size(); i += 1) {
	// falling.push_back(new Tetris::Cubi(window, boardVertex, *textures[game.getTetID()]));
  //     }
  //   }

    window.update();
  } while(!window.close());

  return 0;
}
