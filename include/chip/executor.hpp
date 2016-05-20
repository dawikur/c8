// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP_EXECUTOR_HPP_
#define INCLUDE_CHIP_EXECUTOR_HPP_

#include "callbacks.hpp"
#include "chip/memory.hpp"
#include "chip/opcode.hpp"

namespace chip {

class Executor {
 public:
  Executor();

  void operator()(Opcode const &, Memory &, GetKey const &, UpdateDisplay &);

 private:
  void (*_lookupTable[16])(Opcode const &,
                           Memory &,
                           GetKey const &,
                           UpdateDisplay &);
};

}  // namespace chip

#endif  // INCLUDE_CHIP_EXECUTOR_HPP_
