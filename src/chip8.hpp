// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef SRC_CHIP8_HPP_
#define SRC_CHIP8_HPP_

#include "memory.hpp"
#include "opcode.hpp"
#include "executor.hpp"

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

#endif  // SRC_CHIP8_HPP_
