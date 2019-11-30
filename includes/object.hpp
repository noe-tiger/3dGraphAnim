#pragma once

void draw(glm::vec3 gOrientation, glm::vec3 gPosition, glm::vec3 gScale, GLuint vertexbuffer, GLuint uvbuffer, GLuint normalbuffer, GLuint MatrixID, GLuint ModelMatrixID, GLuint ViewMatrixID, GLuint LightID, GLuint TextureID, GLuint Texture, std::vector<glm::vec3> vertices, GLFWwindow *);

void clanObject(GLuint vertexbuffer, GLuint uvbuffer, GLuint normalbuffer);
