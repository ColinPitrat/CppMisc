#include "bitstream.h"
#include <sstream>
#include <iostream>

InputBitStream::InputBitStream(std::unique_ptr<std::istream> is) : is_(std::move(is)), idx_(-1) {}

bool InputBitStream::getBit() {
  if (idx_ == -1) {
    idx_ = 7;
    char_ = is_->get();
  }
  return char_ & (1 << idx_--);
}

std::unique_ptr<std::istream> istreamFromString(const std::string& input) {
  unsigned char c = 0;
  int i = 0;
  std::string bin_input;
  for (const auto& d : input) {
    if (d != '0' && d != '1') {
      throw std::domain_error("Input string should only contain '0' or '1', got: " + input);
    }
    c *= 2;
    c += (d == '1');
    i++;
    if (i == 8) {
      bin_input += c;
      c = 0;
      i = 0;
    }
  }
  std::unique_ptr<std::istream> iss(new std::istringstream(bin_input));
  return std::move(iss);
}

InputBitStreamForTest::InputBitStreamForTest(const std::string& input) : InputBitStream(istreamFromString(input)) {}

OutputBitStream::OutputBitStream(std::unique_ptr<std::ostream> os) : os_(std::move(os)), idx_(7), char_(0) {}

void OutputBitStream::pushBit(bool value) {
  if (idx_ == -1) {
    idx_ = 7;
    os_->put(char_);
    char_ = 0;
  }
  if (value) {
    char_ |= (1 << idx_);
  }
  idx_--;
}

void OutputBitStream::flush() {
  os_->put(char_);
  char_ = 0;
  os_->flush();
}

OutputBitStreamForTest::OutputBitStreamForTest(std::unique_ptr<std::ostream> os) : OutputBitStream(std::move(os)) {
}

// TODO(cpitrat): Make it behave like OutputBitStream by only outputting every 8 bits or after flush
void OutputBitStreamForTest::pushBit(bool value) {
  os_->put(value ? '1': '0');
}

void OutputBitStreamForTest::flush() {}
