#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>

#include "game.hpp"

namespace Tetris {
  Game::Game(int board_x, int board_y, std::vector<Tetris::Tetrimino> &tetriminos) :
    _tetriminos(tetriminos) {
    std::srand(std::time(nullptr));
    for (int i = 0; i < board_y; i += 1) {
      std::vector<Tetris::Cubi> tmp_arr;
      for (int j = 0; j < board_x; j += 1) {
	Tetris::Cubi tmp; // to replace !
	tmp_arr.push_back(tmp);
      }
      _gameBoard.push_back(tmp_arr);
    }
    _board_x = board_x;
    _board_y = board_y;
    this->getNext();
  }

  Game::~Game() {
  }

  void Game::print() {
    for (int i = 0; i < _gameBoard.size(); i += 1) {
      for (int j = 0; j < _gameBoard[i].size(); j += 1) {
	bool isDropping = false;
	for (int pos = 0; pos < _posNext.size(); pos += 1) {
	  if (j == _posNext[pos][0] && i == _posNext[pos][1]) {
	    isDropping = true;
	  }
	}
	if (isDropping) {
	  std::cout << 'w';
	} else {
	  std::cout << (_gameBoard[i][j].full() ? 'x' : '.');
	}
      }
      std::cout << std::endl;
    }
  }

  Tetris::Tetrimino Game::getNext() {
    _next = _tetriminos[std::rand() % _gameBoard[0].size()];
    _posNext.clear();
    auto format = _next.getFormat();
    for (int i = 0; i < format.size(); i += 1) {
      for (int j = 0; j < format[i].size(); j += 1) {
    	std::vector<int> new_position;
	if (format[i][j] == 'x') {
	  new_position.push_back(((_board_x / 2) - (format[i].size() / 2)) + j);
	  new_position.push_back(i);
	  _posNext.push_back(new_position);
	}
      }
    }
    return _next;
  }

  void Game::rotate(bool wise) {
    if (wise) {
      _next.rotateLeft();
    } else {
      _next.rotateRight();
    }
    _posNext.clear();
    auto format = _next.getFormat();
    for (int i = 0; i < format.size(); i += 1) {
      for (int j = 0; j < format[i].size(); j += 1) {
    	std::vector<int> new_position;
	if (format[i][j] == 'x') {
	  new_position.push_back(((_board_x / 2) - (format[i].size() / 2)) + j);
	  new_position.push_back(i);
	  _posNext.push_back(new_position);
	}
      }
    }
  }

  void Game::side(bool wise) {
    int move = (wise ? 1 : -1);
    for (int i = 0; i < _posNext.size(); i += 1) {
      if (_posNext[i][0] + move < _gameBoard.size()) {
	if (_gameBoard[_posNext[i][1]][_posNext[i][0] + move].full()) {
	  return ;
	}
      } else {
	return ;
      }
    }
    for (int i = 0; i < _posNext.size(); i += 1) {
      _posNext[i][0] += move;
    }
  }
  
  bool Game::update() {
    bool canMove = true;
    for (int i = 0; i < _posNext.size(); i += 1) {
      if (_posNext[i][1] + 1 < _gameBoard.size()) {
	if (_gameBoard[_posNext[i][1] + 1][_posNext[i][0]].full()) {
	  canMove = false;
	}
      } else {
	canMove = false;
      }
    }
    if (canMove) {
      for (int i = 0; i < _posNext.size(); i += 1) {
	_posNext[i][1] += 1;
      }
    } else {
      for (int i = 0; i < _posNext.size(); i += 1) {
	Tetris::Cubi tmp; // replace !!
	tmp.setState(true);
	_gameBoard[_posNext[i][1]][_posNext[i][0]] = tmp;
      }
      this->getNext();
    }
    return canMove;
  } 
}
