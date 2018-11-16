#include "game_of_life.h"
#include <gtest/gtest.h>

static const int GRID_WIDTH = 40;
static const int GRID_HEIGHT = 12;

class GameOfLifeTest : public ::testing::Test {
  protected:
    GameOfLifeTest() : gol_(Width(GRID_WIDTH), Height(GRID_HEIGHT)) {}

    GameOfLife gol_;
};

TEST_F(GameOfLifeTest, RemembersWidthAndHeight) {
  ASSERT_EQ(Width(GRID_WIDTH), gol_.width());
  ASSERT_EQ(Height(GRID_HEIGHT), gol_.height());
}

TEST_F(GameOfLifeTest, InitializedWithDeadCells) {
  for(int x = 0; x < GRID_WIDTH; ++x) {
    for(int y = 0; y < GRID_HEIGHT; ++y) {
      ASSERT_EQ(Cell::DEAD, gol_.get(Coordinates{x, y})) << "for x=" << x << ", y=" << y;
    }
  }
}

TEST_F(GameOfLifeTest, CanSetCellAlive) {
  for(int set_x = 0; set_x < GRID_WIDTH; ++set_x) {
    for(int set_y = 0; set_y < GRID_HEIGHT; ++set_y) {
      gol_.set(Coordinates{set_x, set_y}, Cell::ALIVE);

      for(int x = 0; x < GRID_WIDTH; ++x) {
        for(int y = 0; y < GRID_HEIGHT; ++y) {
          if (x == set_x && y == set_y) {
            ASSERT_EQ(Cell::ALIVE, gol_.get(Coordinates{x, y})) << "for x=" << x << ", y=" << y;
          } else {
            ASSERT_EQ(Cell::DEAD, gol_.get(Coordinates{x, y})) << "for x=" << x << ", y=" << y;
          }
        }
      }

      gol_.set(Coordinates{set_x, set_y}, Cell::DEAD);
    }
  }
}

TEST_F(GameOfLifeTest, IteratesOverExpectedNumberOfCells) {
  int i = 0;

  for(auto cell : gol_) {
    i++;
    ASSERT_EQ(Cell::DEAD, gol_.get(cell));
  }

  ASSERT_EQ(GRID_WIDTH*GRID_HEIGHT, i);
}

TEST_F(GameOfLifeTest, CountNeighbours) {
  // In this first half of the test, the cell is DEAD
  ASSERT_EQ(0, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{0, 0}, Cell::ALIVE);
  ASSERT_EQ(1, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{0, 1}, Cell::ALIVE);
  ASSERT_EQ(2, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  // This is the only place where the cell would be alive in the next generation
  gol_.set(Coordinates{0, 2}, Cell::ALIVE);
  ASSERT_EQ(3, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::ALIVE, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{1, 0}, Cell::ALIVE);
  ASSERT_EQ(4, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{1, 2}, Cell::ALIVE);
  ASSERT_EQ(5, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{2, 0}, Cell::ALIVE);
  ASSERT_EQ(6, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{2, 1}, Cell::ALIVE);
  ASSERT_EQ(7, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{2, 2}, Cell::ALIVE);
  ASSERT_EQ(8, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  // From now on, the cell itself is ALIVE
  gol_.set(Coordinates{1, 1}, Cell::ALIVE);
  ASSERT_EQ(8, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{2, 2}, Cell::DEAD);
  ASSERT_EQ(7, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{2, 1}, Cell::DEAD);
  ASSERT_EQ(6, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{2, 0}, Cell::DEAD);
  ASSERT_EQ(5, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{1, 2}, Cell::DEAD);
  ASSERT_EQ(4, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{1, 0}, Cell::DEAD);
  ASSERT_EQ(3, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::ALIVE, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{0, 2}, Cell::DEAD);
  ASSERT_EQ(2, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::ALIVE, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{0, 1}, Cell::DEAD);
  ASSERT_EQ(1, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));

  gol_.set(Coordinates{0, 0}, Cell::DEAD);
  ASSERT_EQ(0, gol_.count_neighbours(Coordinates{1, 1}, Cell::ALIVE));
  ASSERT_EQ(Cell::DEAD, gol_.next(Coordinates{1, 1}));
}

void PrepareSquare(GameOfLife *gol) {
  gol->set(Coordinates{1, 1}, Cell::ALIVE);
  gol->set(Coordinates{1, 2}, Cell::ALIVE);
  gol->set(Coordinates{2, 1}, Cell::ALIVE);
  gol->set(Coordinates{2, 2}, Cell::ALIVE);
}

TEST_F(GameOfLifeTest, EvolveSquare) {
  GameOfLife gol(Width(4), Height(4)), expected(Width(4), Height(4));
  PrepareSquare(&gol);
  PrepareSquare(&expected);

  gol.evolve();

  ASSERT_EQ(gol, expected);
}

void PrepareHorizontal(GameOfLife *gol) {
  gol->set(Coordinates{2, 1}, Cell::ALIVE);
  gol->set(Coordinates{2, 2}, Cell::ALIVE);
  gol->set(Coordinates{2, 3}, Cell::ALIVE);
}

void PrepareVertical(GameOfLife *gol) {
  gol->set(Coordinates{1, 2}, Cell::ALIVE);
  gol->set(Coordinates{2, 2}, Cell::ALIVE);
  gol->set(Coordinates{3, 2}, Cell::ALIVE);
}

TEST_F(GameOfLifeTest, EvolveBlinker) {
  GameOfLife horizontal(Width(5), Height(5));
  GameOfLife vertical(Width(5), Height(5));
  GameOfLife blinker(Width(5), Height(5));
  PrepareHorizontal(&horizontal);
  PrepareVertical(&vertical);
  PrepareHorizontal(&blinker);

  ASSERT_EQ(blinker, horizontal);

  blinker.evolve();

  ASSERT_EQ(blinker, vertical);

  blinker.evolve();

  ASSERT_EQ(blinker, horizontal);
}
