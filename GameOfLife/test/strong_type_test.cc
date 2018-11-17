#include "strong_type.h"
#include <gtest/gtest.h>

using TestType = StrongType<int, struct TestTypeName>;

TEST(StrongTypeTest, GetReturnsValueFromConstruction) {
  TestType t(42);
  
  ASSERT_EQ(42, t.get());
}

TEST(StrongTypeTest, CanGetOnConstObject) {
  const TestType t(42);
  
  ASSERT_EQ(42, t.get());
}

TEST(StrongTypeTest, CopyConstructionPreservesValue) {
  TestType t1(42);
  TestType t2(t1);
  
  ASSERT_EQ(42, t1.get());
  ASSERT_EQ(42, t2.get());
}

TEST(StrongTypeTest, MoveConstructionTransfersValue) {
  TestType t1(42);
  TestType t2(std::move(t1));
  
  ASSERT_EQ(42, t2.get());
}
