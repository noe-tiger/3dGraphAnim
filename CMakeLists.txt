project(Tetris3d)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17 -fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
  "${CMAKE_SOURCE_DIR}/includes"
)

file(
  GLOB_RECURSE
  sources_tetris
  src/main.cpp
  src/controls.cpp
  src/loader.cpp
  src/object.cpp
  src/window.cpp
  src/texture.cpp
  src/vertex.cpp
)

add_executable(tetris-binary ${sources_tetris})
target_link_libraries(tetris-binary ${CONAN_LIBS})
