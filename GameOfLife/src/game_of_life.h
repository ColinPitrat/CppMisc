#pragma once
#include "strong_type.h"
#include <algorithm>
#include <string>
#include <vector>

using Width = StrongType<int, struct WidthName>;
using Height = StrongType<int, struct HeightName>;

class GameOfLife;

enum Cell {
  DEAD,
  ALIVE
};

struct Coordinates {
  int x, y;
};

Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs);

// TODO: Use strong types here too !
class CellsIterator {
  public:
    CellsIterator(GameOfLife* g, int w, int h) : g_(g), w_(w), h_(h), x_(0), y_(0) {};
    CellsIterator(GameOfLife* g, int w, int h, int x, int y) : g_(g), w_(w), h_(h), x_(x), y_(y) {};

    void operator++();
    void to_end();

    bool operator==(const CellsIterator& other) const {
      return x_ == other.x_ && y_ == other.y_ && w_ == other.w_ && h_ == other.h_;
    }

    bool operator!=(const CellsIterator& other) const {
      return !this->operator==(other);
    }

    Coordinates operator*() const;

  private:
    GameOfLife* g_;
    int w_, h_;
    int x_, y_;
};

class GameOfLife {
  public:
    GameOfLife(Width width, Height height);

    Width width() const;
    Height height() const;
    Cell& get(const Coordinates& coord);
    Cell get(const Coordinates& coord) const;
    void set(const Coordinates& coord, Cell cell);

    void randomize();

    CellsIterator begin();
    CellsIterator end();

    int count_neighbours(const Coordinates& coord, Cell cell) const;
    Cell next(const Coordinates& coord) const;

    void evolve();

    std::string toString();

  private:
    Width width_;
    Height height_;
    std::vector<std::vector<Cell>> grid_;
};

bool operator==(const GameOfLife& lhs, const GameOfLife& rhs);
