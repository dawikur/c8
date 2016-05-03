// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef SRC_RANDOM_HPP_
#define SRC_RANDOM_HPP_

#include <random>

#include "type.hpp"

class Random {
 public:
  static Byte get() {
    static Random r;
    return r.distribution(r.generator);
  }

 private:
  Random() : randomDevice{}, generator{randomDevice()}, distribution{} {}

  std::random_device randomDevice;
  std::mt19937 generator;
  std::uniform_int_distribution<Byte> distribution;
};

#endif  // SRC_RANDOM_HPP_
