// Copyright 2016, Dawid Kurek, dawikur@gmail.com

#include "type.hpp"

#include "gtest/gtest.h"

TEST(type_test, size) {
  ASSERT_EQ(1, sizeof(Byte));
  ASSERT_EQ(2, sizeof(Word));
}


