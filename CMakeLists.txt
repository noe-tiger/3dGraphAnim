project(Tetris3d)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17 -fPIC")

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
  "${CMAKE_SOURCE_DIR}/includes"
  "${CMAKE_SOURCE_DIR}/includes/game"
  "${CMAKE_SOURCE_DIR}/includes/opengl"
)

file(
  GLOB_RECURSE
  sources_tetris
  src/main.cpp

  src/game/controls.cpp
  src/game/game.cpp
  src/game/tetrimino.cpp

  src/opengl/loader.cpp
  src/opengl/object.cpp
  src/opengl/window.cpp
  src/opengl/texture.cpp
  src/opengl/vertex.cpp
)

add_executable(tetris-binary ${sources_tetris})
target_link_libraries(tetris-binary ${CONAN_LIBS})
