#pragma once
#include <utility>

template <typename Type, typename Name>
class StrongType {
  public:
    explicit StrongType(Type const& value) : value_(value) {}
    explicit StrongType(Type && value) : value_(std::move(value)) {}
    Type& get() { return value_; }
    Type const& get() const { return value_; }

  private:
    Type value_;
};
