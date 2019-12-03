#pragma once

#include <GLFW/glfw3.h>

namespace Tetris {
  class Window {
  public:
    // Window();
    Window(const char *vertexFile, const char *shaderFile);
    ~Window();

    void clearScreen();
    void update();

    bool close();

    GLFWwindow *getWindow();
    GLuint getVertexArrayID();
    GLuint getProgramID();
    GLuint getMatrixID();
    GLuint getModelMatrixID();
    GLuint getViewMatrixID();
    GLuint getTextureID();
    GLuint getLightID();
  private:
    GLFWwindow *_window = NULL;

    GLuint _vertexArrayID;
    GLuint _programID;
    GLuint _matrixID;
    GLuint _viewMatrixID;
    GLuint _modelMatrixID;
    GLuint _textureID;
    GLuint _lightID;
  };
}
