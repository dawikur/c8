// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include "type.hpp"

union Memory {
  Byte Raw[0x1000] = { 0x00 };

  struct {
    Byte V[16];                                                                // registers
    Byte VF;                                                                   // register flag
    Word I;                                                                    // memory address
    Byte DT;                                                                   // delay timer
    Byte ST;                                                                   // sound timer
    Word PC;                                                                   // program counter
    Byte SP;                                                                   // stack pointer
    Word Stack[16];                                                            // stack
    Byte Keypad[16 * 5];                                                       // keyboard
    Byte Display[64 * 32 / 8];                                                 // display memory
  };
};

#endif  // INCLUDE_MEMORY_HPP_

