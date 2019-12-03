#include <iostream>
#include <string.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <sstream>
#include <fstream>

bool loadOBJ(
	     const char * path,
	     std::vector<glm::vec3> & out_vertices,
	     std::vector<glm::vec2> & out_uvs,
	     std::vector<glm::vec3> & out_normals) {
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> temp_vertices;
  std::vector<glm::vec2> temp_uvs;
  std::vector<glm::vec3> temp_normals;

  std::cout << "loading object : " << path << std::endl;
  FILE *file = fopen(path, "r");
  if( file == NULL ){
    std::cerr << "file not found !" << path << std::endl;
    return false;
  }
  while(true) {
    char lineHeader[128];
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break;
    if (strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      temp_vertices.push_back(vertex);
    } else if (strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      uv.y = -uv.y;
      temp_uvs.push_back(uv);
    } else if (strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      temp_normals.push_back(normal);
    } else if (strcmp(lineHeader, "f") == 0) {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
			   &vertexIndex[0], &uvIndex[0], &normalIndex[0],
			   &vertexIndex[1], &uvIndex[1], &normalIndex[1],
			   &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if (matches != 9) {
	std::cout << "too complex file, can't be loaded" << std::endl;
	fclose(file);
	return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices.push_back(uvIndex[0]);
      uvIndices.push_back(uvIndex[1]);
      uvIndices.push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    } else {
      char stupidBuffer[1000];
      fgets(stupidBuffer, 1000, file);
    }
  }
  for(unsigned int i=0; i<vertexIndices.size(); i++){
    unsigned int vertexIndex = vertexIndices[i];
    unsigned int uvIndex = uvIndices[i];
    unsigned int normalIndex = normalIndices[i];
    glm::vec3 vertex = temp_vertices[vertexIndex - 1];
    glm::vec2 uv = temp_uvs[uvIndex - 1];
    glm::vec3 normal = temp_normals[normalIndex - 1];
    out_vertices.push_back(vertex);
    out_uvs.push_back(uv);
    out_normals.push_back(normal);
  }
  fclose(file);
  return true;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if(VertexShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
  } else {
    std::cerr << "file not found !" << vertex_file_path << std::endl;
    return 0;
  }
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if(FragmentShaderStream.is_open()) {
    std::stringstream sstr;
    sstr << FragmentShaderStream.rdbuf();
    FragmentShaderCode = sstr.str();
    FragmentShaderStream.close();
  } else {
    std::cerr << "file not found !" << fragment_file_path << std::endl;
    return 0;
  }
  GLint Result = GL_FALSE;
  int InfoLogLength;
  char const *VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    std::cerr << &VertexShaderErrorMessage[0] << std::endl;
  }
  char const *FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    std::cerr << &FragmentShaderErrorMessage[0] << std::endl;
  }
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0){
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    std::cerr << &ProgramErrorMessage[0] << std::endl;
  }
  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);
  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);
  return ProgramID;
}

GLuint loadBMP(const char * imagepath){
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    unsigned char *data;

    std::cout << "loading image : " << imagepath << std::endl;
    FILE *file = fopen(imagepath,"rb");
    if (!file) {
      std::cerr << "file not found ! " << imagepath << std::endl;
      return 0;
    }
    if (fread(header, 1, 54, file) != 54) {
      std::cerr << "wrong bmf format ! " << imagepath << std::endl;
      fclose(file);
      return 0;
    }
    if (header[0]!='B' || header[1]!='M') {
      std::cerr << "wrong bmf format ! " << imagepath << std::endl;
      fclose(file);
      return 0;
    }
    if (*(int*)&(header[0x1E]) != 0) {
      std::cerr << "wrong bmf format ! " << imagepath << std::endl;
      fclose(file); return 0;
    }
    if (*(int*)&(header[0x1C]) != 24) {
      std::cerr << "wrong bmf format ! " << imagepath << std::endl;
      fclose(file); return 0;
    }
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    if (imageSize == 0)
      imageSize = width * height * 3;
    if (dataPos == 0)
      dataPos = 54;
    data = new unsigned char [imageSize];
    fread(data,1,imageSize,file);
    fclose (file);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    delete [] data;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    // GLuint texLoc = glGetUniformLocation(textureID, )
    return textureID;
}
