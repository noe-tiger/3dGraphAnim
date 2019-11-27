#include <string.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>


bool loadOBJ(const char * path,
	     std::vector < glm::vec3 > & out_vertices,
	     std::vector < glm::vec2 > & out_uvs,
	     std::vector < glm::vec3 > & out_normals)
{
  std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
  std::vector< glm::vec3 > temp_vertices;
  std::vector< glm::vec2 > temp_uvs;
  std::vector< glm::vec3 > temp_normals;

  FILE * file = fopen(path, "r");
  if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
  }
  while( 1 ){
    
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) {
      break; // EOF = End Of File. Quit the loop.
    }
    // else : parse lineHeader
    if ( strcmp( lineHeader, "v" ) == 0 ){
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
      temp_vertices.push_back(vertex);
    }else if ( strcmp( lineHeader, "vt" ) == 0 ){
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y );
      temp_uvs.push_back(uv);
    }else if ( strcmp( lineHeader, "vn" ) == 0 ){
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
      temp_normals.push_back(normal);
    }else if ( strcmp( lineHeader, "f" ) == 0 ){
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
      if (matches != 9){
	printf("File can't be read by our simple parser : ( Try exporting with other options\n");
	return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices    .push_back(uvIndex[0]);
      uvIndices    .push_back(uvIndex[1]);
      uvIndices    .push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
      
      for( unsigned int i=0; i < vertexIndices.size(); i++ ){
	unsigned int vertexIndex = vertexIndices[i];
	glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
	out_vertices.push_back(vertex);
      }
    }
  }
  return true;
}


int main()
{
  if( !glfwInit() )
    {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      return -1;
    }
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
  
  // Ouvre une fenêtre et crée son contexte OpenGl
  GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
  window = glfwCreateWindow( 1024, 768, "Tetris 3D", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window.\n" );
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window); // Initialise GLEW
  glewExperimental=true; // Nécessaire dans le profil de base
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  std::vector< glm::vec3 > vertices;
  std::vector< glm::vec2 > uvs;
  std::vector< glm::vec3 > normals; // Won't be used at the moment.
  bool res = loadOBJ("../sources/sample.obj", vertices, uvs, normals);

  do{
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    // Ne dessine rien, on se voit dans le tutoriel 2 !
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();


    if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS) { // get key input
      std::cout << "right" << std::endl;
    }

    // if (glfwJoystickPresent( GLFW_JOYSTICK_1 )) { // get controller input
    //   int axesCount;
    //   const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    //   for (int i = 0; i < axesCount; i += 1) {
    //   	std::cout << axes[i] << " ";
    //   }
    //   // std::cout << std::endl;
    //   std::cout << " == ";

    //   int buttonsCount;
    //   const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
    //   for (int i = 0; i < buttonsCount; i += 1) {
    // 	std::cout << int(buttons[i]) << " ";
    //   }
    //   std::cout << std::endl;
    // }
    
    
  } // Vérifie si on a appuyé sur la touche échap (ESC) ou si la fenêtre a été fermée
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	 glfwWindowShouldClose(window) == 0 );
}
