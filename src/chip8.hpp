// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef SRC_CHIP8_HPP_
#define SRC_CHIP8_HPP_

#include "memory.hpp"
#include "opcode.hpp"
#include "operations.hpp"

class Chip8 {
 public:
  Chip8();

  void execute(bool &waitForKey) {
    operations(command, memory, waitForKey);
  }

  void setKey(Byte const key) {
    memory.V[command.x] = key;
  }

 private:
  Memory memory;
  Opcode command;
  Operations operations;
};

#endif  // SRC_CHIP8_HPP_
