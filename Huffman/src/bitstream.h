#pragma once
#include <istream>
#include <memory>

class InputBitStream {
 public:
  InputBitStream(std::unique_ptr<std::istream>& is);

  bool getBit();

 protected:
  std::unique_ptr<std::istream> is_;
  int idx_;
  int char_;
};

class OutputBitStream {
 public:
  OutputBitStream(std::unique_ptr<std::ostream>& os);

  void pushBit(bool value);
  void flush();

 protected:
  std::unique_ptr<std::ostream> os_;
  int idx_;
  char char_;
};
