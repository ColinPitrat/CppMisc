#pragma once
#include <cstdint>

class GameOfLife {
  public:
    GameOfLife(int x, int y);
    int Get(int x, int y);
    void Set(int x, int y);

};
