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

class CoordsIterator {
  public:
    CoordsIterator(const GameOfLife* g, Width w, Height h) : g_(g), w_(w.get()), h_(h.get()), x_(0), y_(0) {};

    void operator++();
    void to_end();

    bool operator==(const CoordsIterator& other) const {
      return x_ == other.x_ && y_ == other.y_ && w_ == other.w_ && h_ == other.h_;
    }

    bool operator!=(const CoordsIterator& other) const {
      return !this->operator==(other);
    }

    Coordinates operator*() const;

  private:
    const GameOfLife* g_;
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

    CoordsIterator begin() const;
    CoordsIterator end() const;

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
