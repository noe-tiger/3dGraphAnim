#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "loader.hpp"
#include "window.hpp"

namespace Tetris {
  Window::Window(const char *vertexFile, const char *shaderFile) {
    if (!glfwInit()) {
      std::cerr << "failed to init glfw" << std::endl;
      return ;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->_window = glfwCreateWindow(1024, 768, "Tetris 3D - Noe TIGER", NULL, NULL);
    if(this->_window == NULL){
      std::cerr << "failed to init window" << std::endl;
      glfwTerminate();
      return ;
    }
    glfwMakeContextCurrent(this->_window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
      std::cerr << "failed to init glew" << std::endl;
      glfwTerminate();
      return ;
    }
    glfwSetInputMode(this->_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(this->_window, 1024/2, 768/2);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glGenVertexArrays(1, &this->_vertexArrayID);
    glBindVertexArray(this->_vertexArrayID);
    this->_programID = LoadShaders( vertexFile, shaderFile );
    this->_matrixID = glGetUniformLocation(this->_programID, "MVP");
    this->_viewMatrixID = glGetUniformLocation(this->_programID, "V");
    this->_modelMatrixID = glGetUniformLocation(this->_programID, "M");
    this->_textureID  = glGetUniformLocation(this->_programID, "myTextureSampler");
    glUseProgram(this->_programID);
    this->_lightID = glGetUniformLocation(this->_programID, "LightPosition_worldspace");
  }

  Window::~Window() {
    glDeleteProgram(this->_programID);
    glDeleteVertexArrays(1, &this->_vertexArrayID);
    glfwTerminate();
  }

  void Window::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(this->_programID);
  }

  void Window::update() {
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
  }

  bool Window::close() {
    return !(glfwGetKey(this->_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	    glfwWindowShouldClose(this->_window) == 0);
  }

  GLFWwindow *Window::getWindow() {
    return this->_window;
  }

  GLuint Window::getVertexArrayID() {
    return this->_vertexArrayID;
  }

  GLuint Window::getProgramID() {
    return this->_programID;
  }

  GLuint Window::getMatrixID() {
    return this->_matrixID;
  }

  GLuint Window::getModelMatrixID() {
    return this->_modelMatrixID;
  }

  GLuint Window::getViewMatrixID() {
    return this->_viewMatrixID;
  }

  GLuint Window::getTextureID() {
    return this->_textureID;
  }

  GLuint Window::getLightID() {
    return this->_lightID;
  }
}
