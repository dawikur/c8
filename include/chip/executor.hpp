// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP_EXECUTOR_HPP_
#define INCLUDE_CHIP_EXECUTOR_HPP_

#include <cstddef>
#include <cstring>
#include <functional>
#include <random>

#include "memory.hpp"
#include "opcode.hpp"
#include "random.hpp"
#include "type.hpp"

namespace chip {

class Executor {
 public:
  using GetKey = std::function<Byte ()>;

  Executor();

  void operator()(Opcode const opcode, Memory &memory, GetKey const &getKey);

 private:
  void (*_lookupTable[16])(Opcode const, Memory&, GetKey const&);
};

}  // namespace chip

#endif  // INCLUDE_CHIP_EXECUTOR_HPP_
