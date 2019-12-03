
#pragma once

#include <vector>

bool loadOBJ(const char *, std::vector<glm::vec3> &, std::vector<glm::vec2> &, std::vector<glm::vec3> &);
GLuint loadBMP(const char *);
GLuint LoadShaders(const char *, const char *);
