// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "hqx/hqx.hpp"

#include <hqx-1.1/src/hqx.h>

#include <hqx-1.1/src/init.c>
#include <hqx-1.1/src/hq2x.c>
#include <hqx-1.1/src/hq3x.c>
#include <hqx-1.1/src/hq4x.c>

#include <vector>

Hqx::Hqx(Byte const *const memory, unsigned const width, unsigned const height)
  : _input(width * height)
  , _output(width * 4 * height * 4)
  , _memory{memory}
  , _width{width}
  , _height{height} {
  hqxInit();
}

std::vector<uint32_t> const &Hqx::rescale(unsigned const scale) {
  convertMemoryToInput();

  switch (scale) {
    case 1: return _input;
    case 2: hq2x_32(_input.data(), _output.data(), _width, _height); break;
    case 3: hq3x_32(_input.data(), _output.data(), _width, _height); break;
    case 4: hq4x_32(_input.data(), _output.data(), _width, _height); break;
  }

  return _output;
}

void Hqx::convertMemoryToInput() {
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++x) {
      auto const pos = x + (y * _width);
      auto const bit = (_memory[pos / 8] >> (7 - pos % 8)) & 0x01;
      _input[pos] = (bit ? 0x000000FF : 0x00000000);
    }
  }
}

