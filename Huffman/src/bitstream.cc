#include "bitstream.h"

InputBitStream::InputBitStream(std::unique_ptr<std::istream>& is) : is_(std::move(is)), idx_(-1) {}

bool InputBitStream::getBit() {
  if (idx_ == -1) {
    idx_ = 7;
    char_ = is_->get();
  }
  return char_ & (1 << idx_--);
}

OutputBitStream::OutputBitStream(std::unique_ptr<std::ostream>& os) : os_(std::move(os)), idx_(7), char_(0) {}

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
