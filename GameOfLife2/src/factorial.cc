#include <stdexcept>
#include <sstream>
#include "factorial.h"

GameOfLife::GameOfLife(int width, int height) {
  width_ = width;
  height_ = height;
  map_.resize(height);
  for(int i = 0; i < height; i++) {
    map_[i].resize(width);
  }
}

void GameOfLife::Set(int x, int y) {
  if (x < 0 || y < 0 || x >= width_ || y >= height_)
    return;
  map_[y][x] = 1;
}

int GameOfLife::Get(int x, int y) {
  if (x < 0 || y < 0 || x >= width_ || y >= height_)
    return 0;
  return map_[y][x];
}
