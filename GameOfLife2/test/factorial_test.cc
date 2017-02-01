#include "factorial.h"
#include <gtest/gtest.h>

TEST(FactorialTest, GameOfLife)
{
  GameOfLife g(10, 10);
  ASSERT_EQ(0, g.Get(0, 0));

  g.Set(0,0);
  ASSERT_EQ(1, g.Get(0,0));

  g.Set(-1,-1);
  ASSERT_EQ(0, g.Get(-1,-1));

  g.Set(11,11);
  ASSERT_EQ(0, g.Get(11,11));
}

TEST(FactorialTest, GameOfLife2)
{
  GameOfLife g(10, 10);
  ASSERT_EQ(0, g.GetCount(0,0));

  g.Set(1, 1);
  ASSERT_EQ(1, g.GetCount(0,0));
}

TEST(FactorialTest, GameOfLife3)
{
  GameOfLife g(10, 10);
  ASSERT_EQ(0, g.NextStatus(0, 0));

  ASSERT_EQ(1, g.NextStatus(1,2));
}

TEST(FactorialTest, GameOfLife4)
{
  GameOfLife g(10, 10);

  g.NextGeneration();
}
