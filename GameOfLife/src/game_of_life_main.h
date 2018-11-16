#pragma once
#include <string>

// Display a help message describing how to call the program.
std::string usage(const std::string& program_name);

// The real main just call this. It allows testing the whole program.
int game_of_life_main(int argc, char **argv);
