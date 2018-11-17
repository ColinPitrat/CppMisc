#include <cstring>
#include <ctime>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "game_of_life.h"

std::string usage(const std::string &program_name) {
  std::ostringstream msg;
  msg << "Usage: " << program_name << " [<width> <height> | <mapfile>] " << std::endl;
  msg << "Runs Conway's game of life on a <width> x <height> grid or on a grid loaded from <mapfile>." << std::endl;
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

std::unique_ptr<GameOfLife> load_gol(char *filename) {
  std::ifstream inFile;
  inFile.open(filename);
  if (!inFile) {
    std::cerr << "Unable to open '" << filename << "'";
    exit(1);
  }
  // TODO: Move this to game_of_life.h/cc and test it - in particular invalid file with no width/height, odd number of numbers (i.e last point has no y) ...
  int width, height;
  inFile >> width;
  inFile >> height;
  auto result = std::make_unique<GameOfLife>(Width(width), Height(height));
  int x, y;
  while (inFile >> x >> y) {
    result->set(Coordinates{x, y}, Cell::ALIVE);
  }
  inFile.close();
  return result;
}

int game_of_life_main(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    std::cerr << "Unrecognized argument(s)" << std::endl;
    std::cerr << usage(argv[0]);
    return -1;
  }

  std::srand(std::time(nullptr));

  std::unique_ptr<GameOfLife> gol;
  if (argc == 3) {
    int width = parse_uint(argv[1], argv[0]);
    int height = parse_uint(argv[2], argv[0]);
    if (width < 0 || height < 0) return -1;
    gol.reset(new GameOfLife(Width(width), Height(height)));
    gol->randomize();
  } else {
    gol.reset(load_gol(argv[1]).release());
  }

  int generation = 0;
  std::string separator(gol->width().get() - 10, '-');
  while(true) {
    std::cout << generation << separator << std::endl; 
    std::cout << gol->toString() << std::endl;
    gol->evolve();
    usleep(100000);
    generation++;
  }

  return 0;
}
