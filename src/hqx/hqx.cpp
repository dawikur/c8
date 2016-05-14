// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "hqx/hqx.hpp"

#include <hqx-1.1/src/hqx.h>

#include <vector>

namespace hqx {

namespace {

uint32_t convert(Byte const bit) {
  return (bit ? 0x00FFFFFF : 0x00000000);
}

}  // namespace

std::vector<uint32_t> rescale(Byte const *const memory,
                          unsigned const width,
                          unsigned const height,
                          unsigned const scale) {
  std::vector<uint32_t> input{width * height};

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      auto const pos = x + (y * width);
      auto const bit = (memory[pos / 8] >> (7 - pos % 8)) & 0x01;

      input[pos] = convert(bit);
    }
  }

  return input;
}

}  // namespace hqx
