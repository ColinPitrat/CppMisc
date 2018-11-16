#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class Foo {
 public:
  Foo(uint64_t id, std::string content) : id_(id), content_(content) {};

  uint64_t getId() { return id_; }

 private:
  uint64_t id_;
  std::string content_;
};

std::map<uint64_t, Foo*> create_map_from_vector(std::vector<Foo>& foos);
