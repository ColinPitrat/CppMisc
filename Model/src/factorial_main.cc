#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "factorial.h"

std::string usage(const std::string &program_name) {
  std::ostringstream msg;
  msg << "Usage: " << program_name << " <number>" << std::endl;
  msg << "Returns the factorial of <number>";
  return msg.str();
}

int factorial_main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr << "Missing argument" << std::endl;
    std::cerr << usage(argv[0]);
    return -1;
  }

  char *end = nullptr;
  uint64_t n = strtoull(argv[1], &end, 10);
  if (*end != '\0') {
    std::cerr << "Error parsing number " << argv[1] << std::endl;
    std::cerr << usage(argv[0]);
    return -1;
  }

  try {
    std::cout << factorial(n) << std::endl;
  } catch(std::out_of_range &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}
