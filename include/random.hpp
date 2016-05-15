// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_RANDOM_HPP_
#define INCLUDE_RANDOM_HPP_

#include <limits>
#include <random>

#include "type.hpp"

class Random {
 public:
  static Byte get() {
    static Random r;
    return r.distribution(r.generator);
  }

 private:
  Random()
    : generator{}
    , distribution{std::numeric_limits<Byte>::min(),
                   std::numeric_limits<Byte>::max()} {}

  std::mt19937 generator;
  std::uniform_int_distribution<> distribution;
};

#endif  // INCLUDE_RANDOM_HPP_
