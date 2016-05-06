// Copyright 2016, Dawid Kurek, dawikur@gmail.com

#include "opcode.hpp"

#include "gtest/gtest.h"

TEST(opcode_test, opcode) {
  Opcode opcode(0x1234);

  ASSERT_EQ(0x1234, opcode.raw);
  ASSERT_EQ(0x1   , opcode.id);
  ASSERT_EQ(0x0234, opcode.nnn);
  ASSERT_EQ(0x02  , opcode.x);
  ASSERT_EQ(0x003 , opcode.y);
  ASSERT_EQ(0x0004, opcode.n);
  ASSERT_EQ(0x0034, opcode.kk);
}

