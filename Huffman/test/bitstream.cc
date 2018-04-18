#include "bitstream.h"
#include <gtest/gtest.h>
#include <memory>
#include <sstream>

InputBitStream makeInputBitStream(std::string input) {
  std::unique_ptr<std::istream> iss(new std::istringstream(input));
  InputBitStream result(iss);
  return result;
}

TEST(InputBitStream, Construct) {
  InputBitStream bs = makeInputBitStream("abcde");
  // 'a' == 0b01100001
  EXPECT_FALSE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  // 'b' == 0b01100010
  EXPECT_FALSE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  // 'c' == 0b01100011
  EXPECT_FALSE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_FALSE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
  EXPECT_TRUE(bs.getBit());
}

OutputBitStream makeOutputBitStream(std::string& output) {
  std::unique_ptr<std::ostream> oss(new std::ostringstream(output));
  OutputBitStream result(oss);
  return result;
}

// TODO(cpitrat): What to do if number of bits is not a multiple of 8 ?
TEST(OutputBitStream, Construct) {
  std::ostringstream* oss = new std::ostringstream();
  std::unique_ptr<std::ostream> os(oss);
  OutputBitStream bs(os);
  // 'a' == 0b01100001
  bs.pushBit(0);
  bs.pushBit(1);
  bs.pushBit(1);
  bs.pushBit(0);
  bs.pushBit(0);
  bs.pushBit(0);
  bs.pushBit(0);
  bs.pushBit(1);
  // 'b' == 0b01100010
  bs.pushBit(0);
  bs.pushBit(1);
  bs.pushBit(1);
  bs.pushBit(0);
  bs.pushBit(0);
  bs.pushBit(0);
  bs.pushBit(1);
  bs.pushBit(0);
  bs.flush();
  EXPECT_EQ("ab", oss->str());
}
