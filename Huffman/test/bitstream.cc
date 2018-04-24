#include "bitstream.h"
#include <gtest/gtest.h>
#include <memory>
#include <sstream>

InputBitStream makeInputBitStream(std::string input) {
  std::unique_ptr<std::istream> iss(new std::istringstream(input));
  InputBitStream result(std::move(iss));
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

TEST(InputBitStreamForTest, Construct) {
  InputBitStreamForTest bs("011000010110001001100011");
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

TEST(InputBitStreamForTest, RejectInvalidInput) {
  EXPECT_THROW(InputBitStreamForTest bs("01a"), std::domain_error);
  EXPECT_THROW(InputBitStreamForTest bs("012"), std::domain_error);
}

OutputBitStream makeOutputBitStream(std::string& output) {
  std::unique_ptr<std::ostream> oss(new std::ostringstream(output));
  OutputBitStream result(std::move(oss));
  return result;
}

// TODO(cpitrat): What to do if number of bits is not a multiple of 8 ?
TEST(OutputBitStream, Construct) {
  std::ostringstream* oss = new std::ostringstream();
  std::unique_ptr<std::ostream> os(oss);
  OutputBitStream bs(std::move(os));
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

TEST(OutputBitStreamForTest, Construct) {
  std::ostringstream* oss = new std::ostringstream();
  std::unique_ptr<std::ostream> os(oss);
  OutputBitStreamForTest bs(std::move(os));
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
  EXPECT_EQ("0110000101100010", oss->str());
}
