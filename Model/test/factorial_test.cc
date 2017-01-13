#include "factorial.h"
#include <gtest/gtest.h>

TEST(FactorialTest, Factorial_0_is_1)
{
  ASSERT_EQ(1, factorial(0));
}

TEST(FactorialTest, Factorial_2_is_2)
{
  ASSERT_EQ(2, factorial(2));
}

TEST(FactorialTest, Factorial_5_is_120)
{
  ASSERT_EQ(120, factorial(5));
}

TEST(FactorialTest, Factorial_20_is_2432902008176640000)
{
  ASSERT_EQ(2432902008176640000, factorial(20));
}

TEST(FactorialTest, Factorial_21_throws_out_of_range)
{
  ASSERT_THROW(factorial(21), std::out_of_range);
}
