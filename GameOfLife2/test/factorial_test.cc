#include "factorial.h"
#include <gtest/gtest.h>

TEST(FactorialTest, Factorial_0_is_1)
{
  ASSERT_EQ(1, factorial(0));
}
