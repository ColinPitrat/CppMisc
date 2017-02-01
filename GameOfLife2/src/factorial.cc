#include <stdexcept>
#include <sstream>
#include "factorial.h"

GameOfLife::GameOfLife(int x, int y) {
  map_.resize(y);
  for(int i = 0; i < y; i++) {
    map_[i].resize(x);
  }
}

void GameOfLife::Set(int x, int y) {
  map_[y][x] = 1;
}

int GameOfLife::Get(int x, int y) {
  return map_[y][x];
}
