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


	
	std::vector<glm::vec3> vertices2;
  std::vector<glm::vec2> uvs2;
  std::vector<glm::vec3> normals2;
  bool res2 = loadOBJ("../sources/sample.obj", vertices2, uvs2, normals2);

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

	GLuint uvbuffer2;
	glGenBuffers(1, &uvbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer2);
	glBufferData(GL_ARRAY_BUFFER, uvs2.size() * sizeof(glm::vec2), &uvs2[0], GL_STATIC_DRAW);

	GLuint normalbuffer2;
	glGenBuffers(1, &normalbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer2);
	glBufferData(GL_ARRAY_BUFFER, normals2.size() * sizeof(glm::vec3), &normals2[0], GL_STATIC_DRAW);

	vec3 gOrientation2(-1.0, -1.0, -1.0);
	vec3 gPosition2(1.0, 1.0, 1.0);
	vec3 gScale2(1.0, 1.0, 1.0);

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
		gOrientation.x += 0.0031415/ 2.0f * deltaTime;
		gOrientation.z += 0.0031415/ 2.0f * deltaTime;
		gPosition.x += 0.001 * deltaTime;
		gPosition.y += 0.001 * deltaTime;
		gPosition.z += 0.001 * deltaTime;
		// gScale.x -= 0.1 * deltaTime;
		// gScale.y -= 0.1 * deltaTime;
		// gScale.z -= 0.1 * deltaTime;


		
		gOrientation2.y -= 0.0031415/ 2.0f * deltaTime;
		gOrientation2.x -= 0.0031415/ 2.0f * deltaTime;
		gOrientation2.z -= 0.0031415/ 2.0f * deltaTime;
		gPosition2.x -= 0.001 * deltaTime;
		gPosition2.y -= 0.001 * deltaTime;
		gPosition2.z -= 0.001 * deltaTime;
		// gScale.x -= 0.1 * deltaTime;
		// gScale.y -= 0.1 * deltaTime;
		// gScale.z -= 0.1 * deltaTime;


		
		draw(gOrientation, gPosition, gScale, vertexbuffer, uvbuffer, normalbuffer, MatrixID, ModelMatrixID, ViewMatrixID, LightID, TextureID, Texture, vertices, window);
		draw(gOrientation2, gPosition2, gScale2, vertexbuffer2, uvbuffer2, normalbuffer2, MatrixID, ModelMatrixID, ViewMatrixID, LightID, TextureID, Texture, vertices, window);
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	clanObject(vertexbuffer, uvbuffer, normalbuffer);
	clanObject(vertexbuffer2, uvbuffer2, normalbuffer2);
	cleanWindow(programID, Texture, VertexArrayID);
	
	return 0;
}

