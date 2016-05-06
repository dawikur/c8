// Copyright 2016, Dawid Kurek, dawikur@gmail.com

#include <type_traits>

#include "memory.hpp"

#include "gtest/gtest.h"

TEST(memory_test, is_standard_layout) {
  ASSERT_TRUE(std::is_standard_layout<Memory>::value);
}

