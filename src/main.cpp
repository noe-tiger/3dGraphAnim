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
  glm::vec3 gScale(1.0, 1.0, 1.0);
  glm::vec3 gOrientation(0.0, 0.0, 0.0);
  for (int i = 0; i < boardEdge.size(); i += 1) {
    glm::vec3 gPosition(0, 0, -(x > y ? x : y) * 3);
    glm::vec3 gLight(4, 4, -(x > y ? x : y) * 3 + 4);
    
    if (i < y * 2) {
      gPosition.y = y - (i % 2 ? i : i + 1);
      gLight.y = y - (i % 2 ? i : i + 1) + 4;
      gPosition.x = (i % 2 ? x : -x - 2);
      gLight.x = (i % 2 ? x : -x - 2) + 4;
    } else {
      gPosition.x = (x) - (i - 2 * y) * 2;
      gLight.x = (x) - (i - 2 * y) * 2 + 4;
      gPosition.y = -y - 1;
      gLight.y = -y - 1 + 4;
    }
    boardEdge[i].setupPosition(gOrientation, gPosition, gScale, gLight);
    boardEdge[i].draw();
  }
}

void showBoard(Tetris::Game &game, std::vector<Tetris::Cubi *> &falling) {
  int x = game.getFormat()[0];
  int y = game.getFormat()[1];
  glm::vec3 gOrientation(0.0, 0.0, 0.0);
  glm::vec3 gPosition(0.0, 0.0, -(x > y ? x : y) * 3);
  glm::vec3 gScale(1.0, 1.0, 1.0);
  glm::vec3 gLight(4, 4, -(x > y ? x : y) * 3 + 4);
  std::vector<std::vector<Tetris::Cubi *>> board = game.getBoard();
  for (int i = 0; i < board.size(); i += 1) {
    for (int j = 0; j < board[i].size(); j += 1) {
      gPosition.y = y - 1 - i * 2;
      gPosition.x = -x + j * 2;
      gLight.y =  y - 1 - i * 2 + 4;
      gLight.x =  -x + j * 2 + 4;
      // board[i][j].setState(true);
      board[i][j]->setupPosition(gOrientation, gPosition, gScale, gLight);
      board[i][j]->draw();
    }
  }

  gPosition.z += 1;
  std::vector<std::vector<int>> position = game.getFallingPos();
  for (int i = 0; i < falling.size() && i < position.size(); i += 1) {
    gPosition.y = y - 1 - position[i][1] * 2;
    gPosition.x = -x + position[i][0] * 2;
    gLight.y = y - 1 - position[i][1] * 2 + 4;
    gLight.x = -x + position[i][0] * 2 + 4;
    falling[i]->setupPosition(gOrientation, gPosition, gScale, gLight);
    falling[i]->draw();
  }
}

int main()
{
  Tetris::Window window("../vertex.glsm", "../shader.glsm");

  Tetris::Texture texture1("../sources/my_texture.bmp");
  
  Tetris::Vertex objvertex1("../sources/suzanne.obj");
  Tetris::Vertex objvertex2("../sources/suzanne.obj");

  int y = 21;
  int x = 10;
  std::vector<Tetris::Tetrimino> tet = Tetris::getTetrimino("../tetrimino");
  std::vector<Tetris::Texture *> textures = Tetris::getTextures("../sources/tetrimino");
  Tetris::Game game(x, y, tet, window, objvertex1, texture1);
  std::vector<Tetris::Cubi> boardEdge;
  for (int i = 0; i < (x + 2 + (2 * y)); i += 1) {
    Tetris::Cubi object(window, objvertex1, texture1);
    boardEdge.push_back(object);
  }

  std::vector<Tetris::Cubi *> falling;
  for (int i = 0; i < game.getFallingPos().size(); i += 1) {
    falling.push_back(new Tetris::Cubi(window, objvertex2, *textures[game.getTetID()]));
  }

  double lastTime = glfwGetTime();
  double timeout = 0.0f;
  do{
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    bool update = false;
    lastTime = currentTime;
    timeout += deltaTime;
    if (timeout > (1 - 0.01 * game.getScore())) {
      bool ret = game.update(falling, update);
      if (!ret)
      	break ;
      timeout = 0;
    }

    window.clearScreen();
    computeMatricesFromInputs(window.getWindow(), game, falling, update);

    showBoardEdge(boardEdge, x, y);
    showBoard(game, falling);
    if (update) {
      falling.clear();
      for (int i = 0; i < game.getFallingPos().size(); i += 1) {
	falling.push_back(new Tetris::Cubi(window, objvertex2, *textures[game.getTetID()]));
      }
    }
    window.update();
  } while(!window.close());
  
  return 0;
}
