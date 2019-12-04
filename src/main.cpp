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

struct animation {
  std::vector<Tetris::Cubi *> cubi;
  int id;
  int depth;
  float x, y;
  float speed;
};

void animate(Tetris::Window &window, std::vector<Tetris::Tetrimino> &tet,
	     std::vector<Tetris::Texture *> &textures, Tetris::Vertex &vertex, Tetris::Game &game) {
  static std::vector<animation *> anim;
  static size_t speed = 100.0;
  int x = game.getFormat()[0];
  int y = game.getFormat()[1];

  if (anim.size() < 100) {
    animation *newAnim = new animation;
    newAnim->id = std::rand() % textures.size();
    newAnim->speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10));
    newAnim->x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (x * 3))) - (x * 1.5);
    newAnim->y = y * 2 + (std::rand() % 10 - 5);
    newAnim->depth = (std::rand() % 8);
    for (int i = 0; i < game.getFallingPos(tet[newAnim->id], newAnim->x, newAnim->y).size(); i += 1) {
      newAnim->cubi.push_back(new Tetris::Cubi(window, vertex, *textures[newAnim->id]));
    }
    anim.push_back(newAnim);
  }
  for (const auto &elem : anim) {
    elem->y -= elem->speed / 100;
    if (elem->y < -y * 2)
      elem->y = y * 2;
    auto positions = game.getFallingPos(tet[elem->id], elem->x, 1);
    glm::vec3 scale(1.0, 1.0, 1.0);
    glm::vec3 orientation(0.0, 0.0, 0.0);
    for (int i = 0; i < elem->cubi.size(); i += 1) {
      glm::vec3 position(positions[i][0] * 2 + (elem->x), positions[i][1] * 2 + elem->y,
			 -(x > y ? x : y) * 3 - (5 + elem->depth));
      glm::vec3 light(elem->x + 10, elem->y + 10, -(x > y ? x : y) * 3 + 10);
      elem->cubi[i]->setupPosition(orientation, position, scale, light);
      elem->cubi[i]->draw();
    }
  }
  
  // for each elem
  //    faire descendre
  //    if trop bas
  //        pop elem
  // if nb_elem < x * y
  //    map.append(new elem)
}

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
    if (update) {
      falling.clear();
      for (int i = 0; i < game.getFallingPos().size(); i += 1) {
	falling.push_back(new Tetris::Cubi(window, boardVertex, *textures[game.getTetID()]));
      }
    }

    animate(window, tet, textures, boardVertex, game);
    
    window.update();
  } while(!window.close());

  return 0;
}
