// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP8_HPP_
#define INCLUDE_CHIP8_HPP_

#include "executor.hpp"
#include "memory.hpp"
#include "opcode.hpp"

class Chip8 {
 public:
  Chip8();

  void execute() {
    do_execute(command, memory);
  }

  void setKey(Byte const key) {
    memory.V[command.x] = key;
  }

 private:
  Memory memory;
  Opcode command;
  Executor do_execute;
};

#endif  // INCLUDE_CHIP8_HPP_
