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

int main()
{
  GLFWwindow* window = getWindow();

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  // Create and compile our GLSL program from the shaders
  GLuint programID = LoadShaders( "../vertex.glsm", "../shader.glsm" );
  
  // Get a handle for our "MVP" uniform
  GLuint MatrixID = glGetUniformLocation(programID, "MVP");
  GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
  GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
  
  // Load the texture
  GLuint Texture = loadDDS("../sources/uvtemplate.DDS");
  
  // Get a handle for our "myTextureSampler" uniform
  GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
  
  // Get a handle for our "LightPosition" uniform
  glUseProgram(programID);
  GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
  
  
  // Read our .obj file
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals;
  bool res = loadOBJ("../sources/suzanne.obj", vertices, uvs, normals);
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
  
  GLuint uvbuffer;
  glGenBuffers(1, &uvbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
  
  GLuint normalbuffer;
  glGenBuffers(1, &normalbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
  
	
  vec3 gOrientation(1.0, 1.0, 1.0);
  vec3 gPosition(-1.0, -1.0, -1.0);
  vec3 gScale(1.0, 1.0, 1.0);


  Tetris::Cubi object1(MatrixID, ModelMatrixID, ViewMatrixID, LightID, TextureID, window);
  object1.setupObject(vertices.size(), vertexbuffer, uvbuffer, normalbuffer, Texture);
  
  
  double lastTime = glfwGetTime();
  double lastFrameTime = lastTime;
  int nbFrames = 0;
  do{
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastFrameTime);
    nbFrames += 1;
    if (currentTime - lastTime >= 1.0) {
      std::cout << 1000.0/double(nbFrames) << "ms/frame" << std::endl;
      nbFrames = 0;
      lastTime += 1.0;
    }
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use our shader
    glUseProgram(programID);
    
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs(window);
    
    
    
    gOrientation.y += 0.0031415/ 2.0f * deltaTime;
    // gOrientation.x += 0.0031415/ 2.0f * deltaTime;
    // gOrientation.z += 0.0031415/ 2.0f * deltaTime;
    // gPosition.x += 0.001 * deltaTime;
    // gPosition.y += 0.001 * deltaTime;
    // gPosition.z += 0.001 * deltaTime;
    // gScale.x -= 0.1 * deltaTime;
    // gScale.y -= 0.1 * deltaTime;
    // gScale.z -= 0.1 * deltaTime;

    object1.setupPosition(gOrientation, gPosition, gScale, glm::vec3(4, 4, 4));
    object1.draw();
		


    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	 glfwWindowShouldClose(window) == 0 );
  
  cleanWindow(programID, Texture, VertexArrayID);
  
  return 0;
}

