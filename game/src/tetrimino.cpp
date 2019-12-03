#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

#include "tetrimino.hpp"

namespace Tetris {
  Tetrimino::Tetrimino() {}

  Tetrimino::Tetrimino(const char *format) {
    _str_format = format;
    std::vector<char> tmp_vec;

    for (const auto &c : _str_format) {
      if (c == '\n') {
	_format.push_back(tmp_vec);
	tmp_vec.clear();
      } else {
	tmp_vec.push_back(c);
      }
    }
    _format.push_back(tmp_vec);
  }

  Tetrimino::~Tetrimino() {
  }

  void Tetrimino::rotateRight() {
    std::vector<std::vector<char>> new_format;

    for (int i = 0; i < _format[0].size(); i += 1) {
      std::vector<char> tmp_vec;
      for (int j = _format.size() - 1; j >= 0; j -= 1) {
	tmp_vec.push_back(_format[j][i]);
      }
      new_format.push_back(tmp_vec);
    }
    _format = new_format;
  }

  void Tetrimino::rotateLeft() {
    this->rotateRight();
    this->rotateRight();
    this->rotateRight();
  }
    
  void Tetrimino::print() {
    for (const auto &x: _format) {
      for (const auto &y: x) {
	std::cout << y;
      }
      std::cout << std::endl;
    }
  }

  std::vector<std::vector<char>> Tetrimino::getFormat() {
    return _format;
  }

  static std::string getTexturePath(std::string path) {
    std::stringstream ss(path);
    std::string token;
    std::string first;

    std::getline(ss, first, '/');
    while (std::getline(ss, token, '/'));

    for (int i = 0; i < 4; i += 1)
      token.pop_back();
    token = first + "/sources/" + token + ".obj";
    return token;
  }
  
  std::vector<Tetris::Tetrimino> getTetrimino(std::string dirpath) {
    std::vector<Tetris::Tetrimino> tet;

    for(const auto& p: std::filesystem::recursive_directory_iterator(dirpath)) {
      std::ifstream is (p.path(), std::ifstream::binary);
      if (is) {
	is.seekg (0, is.end);
	int length = is.tellg();
	is.seekg (0, is.beg);
	char * buffer = new char [length];
	is.read (buffer,length);
	std::cout << getTexturePath(p.path()) << std::endl;
	tet.push_back(Tetris::Tetrimino(buffer));
	is.close();
	delete [] buffer;
      }
    }
    return tet;
  }
}
