#pragma once

#include <string>

int getFileLength(std::ifstream& is);
std::string readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::string& content);

std::string textToBinary(const std::string& text);
std::string binaryToText(const std::string& bin);

// The real main just call this. It allows testing the whole program.
int huffman_main(int argc, const char **argv);
