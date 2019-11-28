#include <string.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <sstream>
#include <fstream>

void inputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS) { // get key input
      std::cout << "right" << std::endl;
    }

    if (glfwJoystickPresent( GLFW_JOYSTICK_1 )) { // get controller input
      int axesCount;
      const float * axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
      for (int i = 0; i < axesCount; i += 1) {
      	std::cout << axes[i] << " ";
      }
      // std::cout << std::endl;
      std::cout << " == ";

      int buttonsCount;
      const unsigned char * buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
      for (int i = 0; i < buttonsCount; i += 1) {
    	std::cout << int(buttons[i]) << " ";
      }
      std::cout << std::endl;
    }
}

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

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}
	
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

int main()
{
  if( !glfwInit() )
    {
      // fprintf( stderr, "Failed to initialize GLFW\n" );
      return -1;
    }
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
  
  // Ouvre une fenêtre et crée son contexte OpenGl
  GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
  window = glfwCreateWindow( 1024, 768, "Tetris 3D", NULL, NULL);
  if( window == NULL ){
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window); // Initialise GLEW
  glewExperimental=true; // Nécessaire dans le profil de base
  if (glewInit() != GLEW_OK) {
    return -1;
  }
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // std::vector< glm::vec3 > vertices;
  // std::vector< glm::vec2 > uvs;
  // std::vector< glm::vec3 > normals; // Won't be used at the moment.
  // bool res = loadOBJ("../sources/sample.obj", vertices, uvs, normals);
  // load object

  static const GLfloat vertices[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
  };

  static const GLfloat triangle_vertex[] = {
    2.0f, 2.0f, 0.0f,
    3.0f, 2.0f, 0.0f,
    0.0f,  3.0f, 0.0f,
  };

  static GLfloat g_color_buffer_data[12*3*3];
  for (int v = 0; v < 12*3 ; v++){
    g_color_buffer_data[3*v+0] = float(rand() % 100) / 100;
    g_color_buffer_data[3*v+1] = float(rand() % 100) / 100;
    g_color_buffer_data[3*v+2] = float(rand() % 100) / 100;
  }

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint trianglebuffer;
  glGenBuffers(1, &trianglebuffer);
  glBindBuffer(GL_ARRAY_BUFFER, trianglebuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex), triangle_vertex, GL_STATIC_DRAW);

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

  
  GLuint programID = LoadShaders( "../SimpleVertexShader.vertexshader", "../SimpleFragmentShader.fragmentshader" );
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(programID);

  
  do{

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 1024 / (float) 768, 0.1f, 100.0f);
    
    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
    
    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(10,10,10), // Camera is at (4,3,3), in World Space
	glm::vec3(0,0,0), // and looks at the origin
	glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
    
    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
    			  0,
    			  3,                  // size
    			  GL_FLOAT,           // type
    			  GL_FALSE,           // normalized?
    			  0,                  // stride
    			  (void*)0            // array buffer offset
    			  );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
    			  1,
    			  3,                  // size
    			  GL_FLOAT,           // type
    			  GL_FALSE,           // normalized?
    			  0,                  // stride
    			  (void*)0            // array buffer offset
    			  );


    /* draw triangle */
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, trianglebuffer);
    glVertexAttribPointer(
    			  0,
    			  3,                  // size
    			  GL_FLOAT,           // type
    			  GL_FALSE,           // normalized?
    			  0,                  // stride
    			  (void*)0            // array buffer offset
    			  );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    inputs(window);
    
  } // Vérifie si on a appuyé sur la touche échap (ESC) ou si la fenêtre a été fermée
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	 glfwWindowShouldClose(window) == 0 );
}
