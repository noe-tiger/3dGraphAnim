#include <iostream>
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include "controls.hpp"
#include "loader.hpp"
#include "object.hpp"
#include "window.hpp"
#include "texture.hpp"
#include "vertex.hpp"

int main()
{
  Tetris::Window window("../vertex.glsm", "../shader.glsm");

  Tetris::Texture texture1("../sources/my_texture.bmp");
  
  Tetris::Vertex objvertex1("../sources/suzanne.obj");
  
  vec3 gOrientation(0.0, 0.0, 0.0);
  vec3 gPosition(-1.0, -1.0, -1.0);
  vec3 gScale(1.0, 1.0, 1.0);
  vec3 gLight(4, 4, 4);

  Tetris::Cubi object1(window, objvertex1, texture1);
  
  double lastTime = glfwGetTime();
  do{
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;

    window.clearScreen();
    computeMatricesFromInputs(window.getWindow());

    if (glfwJoystickPresent( GLFW_JOYSTICK_1 )) { // get controller input
      int axesCount;
      const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
      
      gOrientation.y += axes[0]/ 20.0f;
      gOrientation.x += axes[1]/ 20.0f;

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

    object1.setupPosition(gOrientation, gPosition, gScale, gLight);
    object1.draw();

    window.update();
  }
  while(!window.close());
  
  return 0;
}
