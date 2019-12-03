#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "game.hpp"
#include "object.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

glm::vec3 position = glm::vec3( 0, 0, 5 ); 
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 20.0f;
float speedController = 0.5f;
float mouseSpeed = 0.005f;

void controller(Tetris::Game &game, std::vector<Tetris::Cubi *> falling, bool &update) {
  static double lastTime = glfwGetTime();
  static double sideToog = 0.0f;
  static double dropToog = 0.0f;
  static double turnToog = 0.0f;
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);
  if (glfwJoystickPresent( GLFW_JOYSTICK_1 )) {
    int axesCount;
    const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    int buttonsCount;
    const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
    horizontalAngle -= mouseSpeed * float(axes[3]);
    verticalAngle   -= mouseSpeed * float(axes[4]);
    glm::vec3 prof(cos(verticalAngle) * sin(horizontalAngle),
		   sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
    glm::vec3 side = glm::vec3(sin(horizontalAngle - 3.14f/2.0f), 0, cos(horizontalAngle - 3.14f/2.0f));
    glm::vec3 height = glm::cross(side, prof);
    position += prof * -axes[1] * speedController;
    position += side * axes[0] * speedController;
    if (axes[6] != 0) {
      if (sideToog < glfwGetTime() - 0.1) {
	game.side((axes[6] < 0 ? false : true));
	sideToog = glfwGetTime();
      }
    } else {
      sideToog = 0.0f;
    }

    if (axes[7] > 0) {
      if (dropToog < glfwGetTime() - 0.1) {
	game.update(falling, update);
	dropToog = glfwGetTime();
      }
    } else {
      dropToog = 0.0f;
    }
    if (axes[2] > 0){
      position += height * speedController;
    }
    if (axes[5] > 0){
      position -= height * speedController;
    }
 
    if (buttons[1] == 1 || buttons[3] == 1) {
      if (turnToog < glfwGetTime() - 0.3) {
	game.rotate(false);
	turnToog = glfwGetTime();
      }
    } else if (buttons[0] == 1 || buttons[2] == 1) {
      if (turnToog < glfwGetTime() - 0.3) {
	game.rotate(true);
	turnToog = glfwGetTime();
      }
    } else {
      turnToog = 0.0f;
    }
  } // add up & down
}

void computeMatricesFromInputs(GLFWwindow *window, Tetris::Game &game,
			       std::vector<Tetris::Cubi *> falling, bool &update){
  static double lastTime = glfwGetTime();
  static double sideToog = 0.0f;
  static double dropToog = 0.0f;
  static double turnToog = 0.0f;
  double currentTime = glfwGetTime();
  float deltaTime = float(currentTime - lastTime);
  double xpos, ypos;

  controller(game, falling, update);
  glfwGetCursorPos(window, &xpos, &ypos);
  glfwSetCursorPos(window, 1024/2, 768/2);
	
  horizontalAngle += mouseSpeed * float(1024/2 - xpos );
  verticalAngle   += mouseSpeed * float( 768/2 - ypos );

    glm::vec3 prof(cos(verticalAngle) * sin(horizontalAngle),
		   sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
    glm::vec3 side = glm::vec3(sin(horizontalAngle - 3.14f/2.0f), 0, cos(horizontalAngle - 3.14f/2.0f));
    glm::vec3 height = glm::cross(side, prof);

    if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
      position += prof * deltaTime * speed;
    }
    if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
      position -= prof * deltaTime * speed;
    }
    if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
      position += side * deltaTime * speed;
    }
    if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
      position -= side * deltaTime * speed;
    }
    if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
      position += height * deltaTime * speed;
    }
    if (glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
      position -= height * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      if (turnToog < glfwGetTime() - 0.3) {
	game.rotate(false);
	turnToog = glfwGetTime();
      }
    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
      if (turnToog < glfwGetTime() - 0.3) {
	game.rotate(true);
	turnToog = glfwGetTime();
      }
    } else {
      turnToog = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      if (sideToog < glfwGetTime() - 0.1) {
	game.side(false);
	sideToog = glfwGetTime();
      }
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      if (sideToog < glfwGetTime() - 0.1) {
	game.side(true);
	sideToog = glfwGetTime();
      }
    } else {
      sideToog = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      if (dropToog < glfwGetTime() - 0.1) {
    	game.update(falling, update);
    	dropToog = glfwGetTime();
      }
    } else {
      dropToog = 0.0f;
    }

    float FoV = initialFoV;
    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(position, position+prof, height);
    lastTime = currentTime;
}
