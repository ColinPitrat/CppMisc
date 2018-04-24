#include "huffman.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

std::string usage(const std::string &program_name) {
  std::ostringstream msg;
  msg << "Usage: " << program_name << " ([-d <file to decompress>] | [-c <file to compress>]) [output file]" << std::endl;
  return msg.str();
}

int getFileLength(std::ifstream& is) {
  int curpos = is.tellg();
  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(curpos, is.beg);
  return length;
}

std::string readFile(const std::string& filename) {
  std::ifstream is(filename.c_str(), std::fstream::binary);
  if (!is) {
    throw std::runtime_error("Couldn't open '" + filename + "' for reading");
  }

  int length = getFileLength(is);

  std::string buffer(length, '\0');
  is.read(&buffer[0], length);

  if (!is) {
    throw std::runtime_error("Couldn't read '" + filename + "'");
  }
  is.close();

  return buffer;
}

void writeFile(const std::string& filename, const std::string& content) {
  std::ofstream os(filename.c_str(), std::fstream::binary);
  if (!os) {
    throw std::runtime_error("Couldn't open '" + filename + "' for writing");
  }
  os.write(content.data(), content.length());
  if (!os) {
    throw std::runtime_error("Couldn't write '" + filename + "'");
  }
  os.close();
  if (!os) {
    throw std::runtime_error("Couldn't close '" + filename + "' after writing");
  }
}

std::string textToBinary(const std::string& text) {
  unsigned char c = 0;
  int i = 0;
  std::string bin;
  for (const auto& d : text) {
    if (d != '0' && d != '1') {
      throw std::domain_error("Input string should only contain '0' or '1', got: " + text);
    }
    c *= 2;
    c += (d == '1');
    i++;
    if (i == 8) {
      bin += c;
      c = 0;
      i = 0;
    }
  }
  // TODO(cpitrat): Padding is an issue, it can result in an additional character at the end of the decompression output.
  // The only way I see to fix this is to add the length of the decompressed output to know when to stop.
  if (i != 0) {
    while (i != 8) {
      c *= 2;
      i++;
    }
    bin += c;
  }
  return bin;
}

std::string binaryToText(const std::string& bin) {
  std::string text;
  for (const auto& c : bin) {
    for (int i = 7; i >= 0; --i) {
      if (c & (1 << i)) {
        text += '1';
      } else {
	text += '0';
      }
    }
  }
  return text;
}

int huffman_main(int argc, const char **argv) {
  if (argc != 4) {
    std::cerr << "Missing argument" << std::endl;
    std::cerr << usage(argv[0]);
    return -1;
  }

  std::string operation = argv[1];
  if (operation == "-d") {
    auto input = readFile(argv[2]);
    auto txtInput = binaryToText(input);
    auto output = decompress(txtInput);
    writeFile(argv[3], output);
  } else if (operation == "-c") {
    auto input = readFile(argv[2]);
    auto output = compress(input);
    auto binOutput = textToBinary(output);
    writeFile(argv[3], binOutput);
  } else {
    std::cerr << "Unknown operation '" << operation << "'" << std::endl;
    std::cerr << usage(argv[0]);
    return -2;
  }

  return 0;
}
