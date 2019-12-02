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

void controller(glm::vec3 *gOrientation) {
  if (glfwJoystickPresent( GLFW_JOYSTICK_1 )) { // get controller input
    int axesCount;
    const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    
    gOrientation->y += axes[0]/ 20.0f;
    gOrientation->x += axes[1]/ 20.0f;
    
    //   for (int i = 0; i < axesCount; i += 1) {
    //   	std::cout << axes[i] << " ";
    //   }
      // std::cout << std::endl;
    //   std::cout << " == ";

      // int buttonsCount;
      // const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
      // for (int i = 0; i < buttonsCount; i += 1) {
    	// std::cout << int(buttons[i]) << " ";
      // }
      // std::cout << std::endl;
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

int main()
{
  Tetris::Window window("../vertex.glsm", "../shader.glsm");

  Tetris::Texture texture1("../sources/my_texture.bmp");
  
  Tetris::Vertex objvertex1("../sources/suzanne.obj");

  // int x = 10;
  // int y = 21;
  // std::vector<Tetris::Tetrimino> tet = Tetris::getTetrimino("../tetrimino");
  // Tetris::Game game(x, y, tet);

  glm::vec3 gOrientation(0.0, 0.0, 0.0);
  glm::vec3 gPosition(-1.0, -1.0, -1.0);
  glm::vec3 gScale(1.0, 1.0, 1.0);
  glm::vec3 gLight(4, 4, 4);

  // std::vector<Tetris::Cubi> boardEdge;

  // for (int i = 0; i < (x + 2 + (2 * y)); i += 1) {
  //   Tetris::Cubi object(window, objvertex1, texture1);
  //   boardEdge.push_back(object);
  // }
  
  double lastTime = glfwGetTime();
  do{
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;

    window.clearScreen();
    computeMatricesFromInputs(window.getWindow());

    controller(&gOrientation);
    
    // for (int i = 0; i < 1 // boardEdge.size()
    // 	   ; i += 1) {
    //   boardEdge[i].setupPosition(gOrientation, gPosition, gScale, gLight);
    //   boardEdge[i].draw();
    // }

    // object1.setupPosition(gOrientation, gPosition, gScale, gLight);
    // object1.draw();

    window.update();
  }
  while(!window.close());
  
  return 0;
}
