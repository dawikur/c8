// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_HQX_HQX_HPP_
#define INCLUDE_HQX_HQX_HPP_

#include <vector>

#include "type.hpp"

class Hqx {
 public:
  using Buffer = std::vector<uint32_t>;

  Hqx(Byte const * const memory, unsigned const width, unsigned const height);

  void rescale(unsigned const scale);
  Buffer const &operator()() const;

 private:
  void convertMemoryToInput();

  Buffer _input;
  Buffer _output;
  unsigned _scale;

  Byte const * const _memory;
  unsigned const _width;
  unsigned const _height;
};

#endif  // INCLUDE_HQX_HQX_HPP_

