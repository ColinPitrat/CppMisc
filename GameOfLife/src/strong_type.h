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

template <typename Type, typename Name>
bool operator==(const StrongType<Type, Name> lhs, const StrongType<Type, Name> rhs)
{
  return lhs.get() == rhs.get();
}

template <typename Type, typename Name>
bool operator!=(const StrongType<Type, Name> lhs, const StrongType<Type, Name> rhs)
{
  return !operator==(lhs, rhs);
}

