// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_HQX_HQX_HPP_
#define INCLUDE_HQX_HQX_HPP_

#include <vector>

#include "type.hpp"

namespace hqx {

std::vector<uint32_t> rescale(Byte const *const memory,
                              unsigned const width,
                              unsigned const height,
                              unsigned const scale);

}  // namespace hqx

#endif  // INCLUDE_HQX_HQX_HPP_

