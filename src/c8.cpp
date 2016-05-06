// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include <iostream>
#include <string>

#include "c8form.hpp"
#include "chip8.hpp"

int main(int argc, char *argv[]) {
  try {
    Chip8 chip8;

    C8form form;

    form.fileChoosen([&chip8](std::string const &file) { chip8.load(file); });

    if (argc > 1) {
      chip8.load(argv[1]);
    }

    form.exec();
  } catch (std::exception e) {
    std::cout << "[!] " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
