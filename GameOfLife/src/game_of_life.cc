#include "game_of_life.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs) {
  Coordinates r;
  r.x = lhs.x + rhs.x;
  r.y = lhs.y + rhs.y;
  return r;
}

void CoordsIterator::operator++() {
  x_++;
  if (x_ >= w_) {
    x_ = 0;
    y_++;
  }
}

void CoordsIterator::to_end() {
  x_ = 0;
  y_ = h_;
}

Coordinates CoordsIterator::operator*() const {
  return Coordinates{x_, y_};
}

GameOfLife::GameOfLife(Width width, Height height) : width_(width), height_(height),
  grid_(width.get(), std::vector<Cell>(height.get(), Cell::DEAD)) {}

Width GameOfLife::width() const { return width_; }
Height GameOfLife::height() const { return height_; }

// This doesn't work for values <= -max_val but we really only care about -1 for negative values
int wrap(int val, int max_val) {
  return (val + max_val) % max_val;
}

Cell& GameOfLife::get(const Coordinates& coord) {
  return grid_[wrap(coord.x, width_.get())][wrap(coord.y, height_.get())];
}

Cell GameOfLife::get(const Coordinates& coord) const {
  return grid_[wrap(coord.x, width_.get())][wrap(coord.y, height_.get())];
}

void GameOfLife::set(const Coordinates& coord, Cell cell) {
  get(coord) = cell;
}

void GameOfLife::randomize() {
  std::for_each(begin(), end(), [&](Coordinates coord) {
    this->set(coord, static_cast<Cell>(std::rand() % 2));
  });
}

CoordsIterator GameOfLife::begin() const {
  return CoordsIterator(this, width_, height_);
}

CoordsIterator GameOfLife::end() const {
  CoordsIterator result(this, width_, height_);
  result.to_end();
  return result;
}

int GameOfLife::count_neighbours(const Coordinates& coord, Cell cell) const {
  static std::vector<Coordinates> neighbours = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
  return std::count_if(neighbours.begin(), neighbours.end(), [this, coord, cell](const Coordinates& delta) {
    return (this->get(coord + delta) == cell);
  });
}

Cell GameOfLife::next(const Coordinates& coord) const {
  static std::map<Cell, std::vector<Cell>> transitions = {
    { Cell::DEAD,  { Cell::DEAD, Cell::DEAD, Cell::DEAD,  Cell::ALIVE, Cell::DEAD, Cell::DEAD, Cell::DEAD, Cell::DEAD, Cell::DEAD }},
    { Cell::ALIVE, { Cell::DEAD, Cell::DEAD, Cell::ALIVE, Cell::ALIVE, Cell::DEAD, Cell::DEAD, Cell::DEAD, Cell::DEAD, Cell::DEAD }},
  };
  return transitions[get(coord)][count_neighbours(coord, Cell::ALIVE)];
}

bool operator==(const GameOfLife& lhs, const GameOfLife& rhs) {
  if (lhs.width().get() != rhs.width().get() || lhs.height().get() != rhs.height().get()) return false;
  for (const auto& coord : lhs) {
    if (lhs.get(coord) != rhs.get(coord)) return false;
  }
  return true;
}

void GameOfLife::evolve() {
  GameOfLife new_gol(width(), height());
  std::for_each(begin(), end(), [&](const Coordinates& coord) {
    new_gol.set(coord, next(coord));
  });
  std::for_each(begin(), end(), [&](Coordinates coord) {
    this->set(coord, new_gol.get(coord));
  });
}

std::string GameOfLife::toString() {
  int w = width().get() + 1;
  int h = height().get();
  std::string result(w*h, ' ');
  for (const auto& coord : *this) {
    if (get(coord) == Cell::ALIVE) result[w*coord.y+coord.x] = '#';
  }
  for (int y = 1; y <= h; ++y) {
    result[w*y-1] = '\n';
  }

  /* This is the reference implementation
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w-1; ++x) {
      if (get(Coordinates{x, y}) == Cell::ALIVE) result[w*y+x] = '#';
    }
    result[w*y+w-1] = '\n';
  }
  */

  /* This misses the \n at end of lines ... would be nice to have a clean way to add it
  std::transform(begin(), end(), back_inserter(result), [=](const Coordinates& coord) {
    return (get(coord) == Cell::ALIVE) ? '#' : ' ';
  });
  */
  return result;
}
