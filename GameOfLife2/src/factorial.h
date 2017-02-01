#pragma once
#include <cstdint>
#include <vector>

class GameOfLife {
  public:
    GameOfLife(int x, int y);
    int Get(int x, int y);
    void Set(int x, int y);
    int GetCount(int x, int y);
  private:
    std::vector<std::vector<int>> map_;
    int width_;
    int height_;
};
