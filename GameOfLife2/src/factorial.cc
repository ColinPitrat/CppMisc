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

int GameOfLife::GetCount(int x, int y) {
  int result = 0;
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      result += Get(x+i, y+j);
    }
  }
  return result - Get(x, y);
}

int GameOfLife::NextStatus(int status, int nei) {
  if (nei == 2)
  return status;
  if (nei == 3)
    return 1;
  return 0;
}

void GameOfLife::NextGeneration() {
  auto copy = map_;
  for(int x = 0; x < width_; x++) {
    for(int y = 0; y < height_; y++) {
      copy[y][x] = NextStatus(map_[y][x], GetCount(x, y));
    }
  }
  map_ = copy;
}
