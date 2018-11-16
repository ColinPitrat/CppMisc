#include <cstring>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "game_of_life.h"

std::string usage(const std::string &program_name) {
  std::ostringstream msg;
  msg << "Usage: " << program_name << " <width> <height> " << std::endl;
  msg << "Runs Conway's game of life on a <width> x <height> grid." << std::endl;
  return msg.str();
}

int parse_uint(char *arg, char *progname) {
  char *end = nullptr;
  uint64_t n = strtoull(arg, &end, 10);
  if (*end != '\0') {
    std::cerr << "Error parsing number " << arg << std::endl;
    std::cerr << usage(progname);
    return -1;
  }
  return n;
}

int game_of_life_main(int argc, char **argv) {
  if(argc != 3) {
    std::cerr << "Unrecognized argument(s)" << std::endl;
    std::cerr << usage(argv[0]);
    return -1;
  }

  int width = parse_uint(argv[1], argv[0]);
  int height = parse_uint(argv[2], argv[0]);
  if (width < 0 || height < 0) return -1;

  std::srand(std::time(nullptr));
  GameOfLife gol{Width(width), Height(height)};
  gol.randomize();
  std::string separator(width, '-');
  while(true) {
    std::cout << separator << std::endl; 
    std::cout << gol.toString() << std::endl;
    gol.evolve();
    usleep(100000);
  }

  return 0;
}
