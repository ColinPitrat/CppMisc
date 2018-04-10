#include "huffman_main.h"
#include <gtest/gtest.h>
#include <vector>

TEST(HuffmanMainTest, NoArgument) {
  std::vector<const char*> argv = {"./huffman"};
  EXPECT_EQ(-1, huffman_main(argv.size(), &argv[0]));
}

TEST(HuffmanMainTest, NoFile) {
  std::vector<const char*> argv = {"./huffman", "-c"};
  EXPECT_EQ(-1, huffman_main(argv.size(), &argv[0]));
}

TEST(HuffmanMainTest, WrongOperation) {
  std::vector<const char*> argv = {"./huffman", "-k", "toto"};
  EXPECT_EQ(-2, huffman_main(argv.size(), &argv[0]));
}
