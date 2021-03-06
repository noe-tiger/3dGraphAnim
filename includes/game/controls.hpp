
#pragma once

#include <vector>

#include "game.hpp"
#include "object.hpp"

glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void inputs(GLFWwindow *, Tetris::Game &game, std::vector<Tetris::Cubi *> falling, bool &update);
void controller(Tetris::Game &game, std::vector<Tetris::Cubi *> falling, bool &update);
