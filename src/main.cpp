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

void controller(glm::vec3 *gOrientation, Tetris::Game &game) {
  static double sideToog = 0.0f;
  static double turnToog = 0.0f;
  if (glfwJoystickPresent( GLFW_JOYSTICK_1 )) { // get controller input
    int axesCount;
    const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    
    // gOrientation->y += axes[0]/ 20.0f;
    // gOrientation->x += axes[1]/ 20.0f;

    if (axes[6] != 0) {
      if (sideToog < glfwGetTime() - 0.1) {
	game.side((axes[6] < 0 ? true : false));
	sideToog = glfwGetTime();
      }
    } else {
      sideToog = 0.0f;
    }
    
      // for (int i = 0; i < axesCount; i += 1) {
      // 	std::cout << axes[i] << " ";
      // }
      // std::cout << std::endl;
      // std::cout << " == ";

      int buttonsCount;
      const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
      // for (int i = 0; i < buttonsCount; i += 1) {
      // 	std::cout << int(buttons[i]) << " ";
      // }
      // std::cout << std::endl;

      if (buttons[1] == 1) {
	if (turnToog < glfwGetTime() - 0.3) {
	  game.rotate(true);
	  turnToog = glfwGetTime();
	}
      } else if (buttons[0] == 1) {
	if (turnToog < glfwGetTime() - 0.3) {
	  game.rotate(false);
	  turnToog = glfwGetTime();
	}
      } else {
	turnToog = 0.0f;
      }
  }


		// gOrientation.y += 0.000031415/ 2.0f * deltaTime;
    // gOrientation.x += 0.000031415/ 2.0f * deltaTime;
    // gOrientation.z += 0.000031415/ 2.0f * deltaTime;
    // gPosition.x += 0.001 * deltaTime;
    // gPosition.y += 0.001 * deltaTime;
    // gPosition.z += 0.001 * deltaTime;
    // gScale.x -= 0.1 * deltaTime;
    // gScale.y -= 0.1 * deltaTime;
    // gScale.z -= 0.1 * deltaTime;
}

void showBoardEdge(std::vector<Tetris::Cubi> &boardEdge, int x, int y, glm::vec3 &gOrientation) {
  glm::vec3 gScale(1.0, 1.0, 1.0);
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
      gPosition.x = x - 2 - j * 2;
      gLight.y =  y - 1 - i * 2 + 4;
      gLight.x =  x - 2 - i * 2 + 4;
      // board[i][j].setState(true);
      board[i][j]->setupPosition(gOrientation, gPosition, gScale, gLight);
      board[i][j]->draw();
    }
  }

  // gPosition.z += 2;
  std::vector<std::vector<int>> position = game.getFallingPos();
  for (int i = 0; i < falling.size() && i < position.size(); i += 1) {
    gPosition.y = y - 1 - position[i][1] * 2;
    gPosition.x = x - 2 - position[i][0] * 2;
    gLight.y = y - 1 - position[i][1] * 2 + 4;
    gLight.x = x - 1 - position[i][0] * 2 + 4;
    falling[i]->setupPosition(gOrientation, gPosition, gScale, gLight);
    falling[i]->draw();
  }
}

int main()
{
  Tetris::Window window("../vertex.glsm", "../shader.glsm");

  Tetris::Texture texture1("../sources/my_texture.bmp");
  
  Tetris::Vertex objvertex1("../sources/suzanne.obj");
  Tetris::Vertex objvertex2("../sources/sample.obj");

  int y = 10;
  int x = 10;
  std::vector<Tetris::Tetrimino> tet = Tetris::getTetrimino("../tetrimino");
  Tetris::Game game(x, y, tet, window, objvertex1, texture1);

  // for (int i = 0; i < tet.size(); i += 1) {
  //   tet[i].print();
  //   std::cout << std::endl;
  // }

  glm::vec3 gOrientation(0.0, 0.0, 0.0);
  // glm::vec3 gPosition(-1.0, -1.0, -1.0);
  // glm::vec3 gScale(1.0, 1.0, 1.0);
  // glm::vec3 gLight(4, 4, -(x > y ? x : y) * 3 + 4);

  std::vector<Tetris::Cubi> boardEdge;

  for (int i = 0; i < (x + 2 + (2 * y)); i += 1) {
    Tetris::Cubi object(window, objvertex1, texture1);
    boardEdge.push_back(object);
  }

  std::vector<Tetris::Cubi *> falling;
  Tetris::Tetrimino lel = game.getFalling();
  Tetris::Texture fallingTexture = lel.getTexture();
  for (int i = 0; i < game.getFallingPos().size(); i += 1) {
    falling.push_back(new Tetris::Cubi(window, objvertex2, fallingTexture));
  }

  double lastTime = glfwGetTime();
  double timeout = 0.0f;
  do{
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;
    timeout += deltaTime;
    if (timeout > 1) {
      bool ret = game.update(falling);
      if (!ret)
	break ;
      timeout = 0;
    }

    window.clearScreen();
    computeMatricesFromInputs(window.getWindow());

    controller(&gOrientation, game);
    showBoardEdge(boardEdge, x, y, gOrientation);
    showBoard(game, falling);

    window.update();
  } while(!window.close());
  
  return 0;
}
