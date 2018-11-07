#include "create_map_from_vector.h"
#include <gtest/gtest.h>

#include <map>
#include <vector>

TEST(CreateMapFromVector, EmptyMapForEmptyVector)
{
  auto input = std::vector<Foo>{};
  auto expected = std::map<uint64_t, Foo*>{};

  auto result = create_map_from_vector(input);

  ASSERT_EQ(expected, result);
}

TEST(CreateMapFromVector, MapForOrderedVector)
{
  auto input = std::vector<Foo>{ Foo(0, "Hello"), Foo(1, "World") };
  auto expected = std::map<uint64_t, Foo*> {
	  {0, &input[0]},
	  {1, &input[1]} 
  };

  auto result = create_map_from_vector(input);

  ASSERT_EQ(expected, result);
}

TEST(CreateMapFromVector, MapForUnorderedVector)
{
  auto input = std::vector<Foo>{ Foo(1, "World"), Foo(0, "Hello") };
  auto expected = std::map<uint64_t, Foo*> {
	  {0, &input[1]},
	  {1, &input[0]} 
  };

  auto result = create_map_from_vector(input);

  ASSERT_EQ(expected, result);
}
