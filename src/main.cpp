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

GLuint loadBMP_custom(const char * imagepath){

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file){
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if ( fread(header, 1, 54, file)!=54 ){ 
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    fclose(file); return 0;}
	if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    fclose(file); return 0;}

	// Read the information about the image
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	// Everything is in memory now, the file can be closed.
	fclose (file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete [] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}


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
//   GLuint Texture = loadDDS("../sources/uvtemplate.DDS");
  GLuint Texture = loadBMP_custom("../sources/my_texture.bmp");
  
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
  vec3 gLight(4, 4, 4);

  Tetris::Cubi object1(MatrixID, ModelMatrixID, ViewMatrixID, LightID, TextureID, vertices.size(), vertexbuffer, uvbuffer, normalbuffer, Texture);
  
  
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    
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

    object1.setupPosition(gOrientation, gPosition, gScale, gLight);
    object1.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	 glfwWindowShouldClose(window) == 0 );
  
  cleanWindow(programID, Texture, VertexArrayID);
  
  return 0;
}

