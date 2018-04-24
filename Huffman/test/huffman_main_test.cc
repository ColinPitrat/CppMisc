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
  std::vector<const char*> argv = {"./huffman", "-k", "toto", "titi"};
  EXPECT_EQ(-2, huffman_main(argv.size(), &argv[0]));
}

TEST(HuffmanMainTest, TextToBinary) {
  EXPECT_EQ("a", textToBinary("01100001"));
  EXPECT_EQ("ab", textToBinary("0110000101100010"));
  EXPECT_EQ("ab0", textToBinary("01100001011000100011"));
}

TEST(HuffmanMainTest, BinaryToText) {
  EXPECT_EQ("01100001", binaryToText("a"));
  EXPECT_EQ("0110000101100010", binaryToText("ab"));
}
