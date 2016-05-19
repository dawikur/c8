// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "hqx/hqx.hpp"

inline uint32_t abs(uint32_t _X)
{
  return _X;
}

#define DLL_EXPORT

#include <hqx-1.1/src/hqx.h>

#include <hqx-1.1/src/init.c>
#include <hqx-1.1/src/hq2x.c>

#undef PIXEL00_20
#undef PIXEL01_10
#undef PIXEL01_12
#undef PIXEL01_21
#undef PIXEL01_60
#undef PIXEL01_61
#undef PIXEL10_10
#undef PIXEL10_11
#undef PIXEL10_21
#undef PIXEL10_60
#undef PIXEL10_61
#undef PIXEL11_70

#include <hqx-1.1/src/hq3x.c>
#include <hqx-1.1/src/hq4x.c>

#undef DLL_EXPORT

#include <vector>

Hqx::Hqx(Byte const *const memory, unsigned const width, unsigned const height)
  : _input(width * height)
  , _output(width * 4 * height * 4)
  , _scale(1)
  , _memory{memory}
  , _width{width}
  , _height{height} {
  hqxInit();
}

Hqx::Buffer const &Hqx::operator()() const {
  if (_scale == 1) {
    return _input;
  }
  return _output;
}

void Hqx::rescale(unsigned const scale) {
  convertMemoryToInput();

  switch (scale) {
    case 1: break;
    case 2: hq2x_32(_input.data(), _output.data(), _width, _height); break;
    case 3: hq3x_32(_input.data(), _output.data(), _width, _height); break;
    case 4: hq4x_32(_input.data(), _output.data(), _width, _height); break;

    default: return;
  }

  _scale = scale;
}

void Hqx::convertMemoryToInput() {
  for (unsigned y = 0; y < _height; ++y) {
    for (unsigned x = 0; x < _width; ++x) {
      auto const pos = x + (y * _width);
      auto const bit = (_memory[pos / 8] >> (7 - pos % 8)) & 0x01;
      _input[pos] = (bit ? 0x000000FF : 0x00000000);
    }
  }
}

