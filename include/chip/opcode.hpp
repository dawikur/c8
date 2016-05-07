// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP_OPCODE_HPP_
#define INCLUDE_CHIP_OPCODE_HPP_

#include "type.hpp"

namespace chip {

struct Opcode {
  Opcode() : Opcode(0x00) {}

  explicit Opcode(Word const opcode)
    : raw{opcode}
    , nnn{static_cast<Word>( opcode & 0x0FFF)       }
    , id {static_cast<Byte>((opcode & 0xF000) >> 12)}
    , x  {static_cast<Byte>((opcode & 0x0F00) >>  8)}
    , y  {static_cast<Byte>((opcode & 0x00F0) >>  4)}
    , n  {static_cast<Byte>( opcode & 0x000F)       }
    , kk {static_cast<Byte>( opcode & 0x00FF)       } {}

  Word raw;
  Word nnn;
  Byte id, x, y, n, kk;
};

}  // namespace chip

#endif  // INCLUDE_CHIP_OPCODE_HPP_
