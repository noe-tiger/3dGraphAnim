#pragma once

namespace Tetris {
  class Window {
  public:
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

// GLFWwindow * getWindow();
// void cleanWindow(GLuint programID, GLuint VertexArrayID);

  // GLuint VertexArrayID;
  // glGenVertexArrays(1, &VertexArrayID);
  // glBindVertexArray(VertexArrayID);
  // // Create and compile our GLSL program from the shaders
  // GLuint programID = LoadShaders( "../vertex.glsm", "../shader.glsm" );
  // // Get a handle for our "MVP" uniform
  // GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  // GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
  // GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
  // // Load the texture
  // // GLuint Texture = loadBMP_custom("../sources/my_texture.bmp");
  // Tetris::Texture texture1("../sources/my_texture.bmp");
  // // Get a handle for our "myTextureSampler" uniform
  // GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
  // // Get a handle for our "LightPosition" uniform
  // glUseProgram(programID);
  // GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

