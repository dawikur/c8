// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include <iostream>
#include <string>

#include "chip/chip8.hpp"
#include "gui/c8form.hpp"

int main(int argc, char *argv[]) {
  try {
    chip::Chip8 chip8;
    gui::C8form form{chip8.getDisplay()};

    //chip8.getKey();
    form.fileChoosen(chip8.fileChoosenCallback());
    form.keyEvent(chip8.keyEventCallback());

    if (argc > 1) {
      chip8.fileChoosenCallback()(argv[1]);
    }

    form.exec();
  } catch (std::exception e) {
    std::cout << "[!] " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
