
#pragma once

#include "game.hpp"
#include "object.hpp"

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void computeMatricesFromInputs(GLFWwindow *);
void controller(Tetris::Game &game, std::vector<Tetris::Cubi *> falling, bool &update);
