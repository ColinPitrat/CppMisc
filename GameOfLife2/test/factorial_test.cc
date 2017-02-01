#include "factorial.h"
#include <gtest/gtest.h>

TEST(FactorialTest, GameOfLife)
{
  GameOfLife g(10, 10);
  ASSERT_EQ(0, g.Get(0, 0));

  g.Set(0,0);
    ASSERT_EQ(0, g.Get(0,0));
}
