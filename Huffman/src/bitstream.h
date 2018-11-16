#pragma once
#include <istream>
#include <memory>

class InputBitStream {
 public:
  InputBitStream(std::unique_ptr<std::istream> is);

  bool getBit();

 protected:
  std::unique_ptr<std::istream> is_;
  int idx_;
  int char_;
};

class InputBitStreamForTest : public InputBitStream {
 public:
  InputBitStreamForTest(const std::string& input);
};

class OutputBitStream {
 public:
  OutputBitStream(std::unique_ptr<std::ostream> os);

  virtual void pushBit(bool value);
  virtual void flush();

 protected:
  std::unique_ptr<std::ostream> os_;
  int idx_;
  char char_;
};

class OutputBitStreamForTest : public OutputBitStream {
 public:
  OutputBitStreamForTest(std::unique_ptr<std::ostream> os);

  void pushBit(bool value) override;
  void flush() override;
};
