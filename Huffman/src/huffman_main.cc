#include "huffman.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::string usage(const std::string &program_name) {
  std::ostringstream msg;
  msg << "Usage: " << program_name << " ([-d <file to decompress>] | [-c <file to compress>])" << std::endl;
  return msg.str();
}

int huffman_main(int argc, const char **argv) {
  if (argc != 3) {
    std::cerr << "Missing argument" << std::endl;
    std::cerr << usage(argv[0]);
    return -1;
  }

  std::string operation = argv[1];
  if (operation == "-d") {
  } else if (operation == "-c") {
  } else {
    std::cerr << "Unknown operation '" << operation << "'" << std::endl;
    std::cerr << usage(argv[0]);
    return -2;
  }

  return 0;
}
