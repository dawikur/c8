// Copyright 2016, Dawid Kurek, dawikur@gmail.com

#include <type_traits>

#include "../src/executor.hpp"

#include "gtest/gtest.h"

class executor_test : public ::testing::Test {
 protected:
  void SetUp() override {
    memset(memory.Raw, 0, sizeof (memory.Raw));

    for (int i = 0; i < 16; ++i) {
      memory.V[i] = i;
    }
  }

  void execute(Word const word) {
    do_execute(Opcode{word}, memory);
  }

  Executor do_execute;
  Memory memory;
};

TEST_F(executor_test, 0_CLS_clear_the_display) {
  memory.Display[0] = 0x12;

  execute(0x00E0);

  ASSERT_EQ(0x00, memory.Display[0]);
}

TEST_F(executor_test, 0_RET_return_from_subroutine) {
  memory.SP = 1;
  memory.Stack[1] = 0x54;

  execute(0x00EE);

  ASSERT_EQ(0, memory.SP);
  ASSERT_EQ(0x54, memory.PC);
}

TEST_F(executor_test, 1_JP_kump_to_location_nnn) {
  memory.PC = 0x01;
  execute(0x1234);

  ASSERT_EQ(0x0234, memory.PC);
}

TEST_F(executor_test, 2_CALL_call_subroutine_at_nnn) {
  memory.PC = 0x5678;

  execute(0x2345);

  ASSERT_EQ(1, memory.SP);
  ASSERT_EQ(0x5678, memory.Stack[memory.SP]);
  ASSERT_EQ(0x0345, memory.PC);
}

TEST_F(executor_test, 3_SE_skip_next_instruction_if_Vx_eq_kk_true) {
  memory.PC = 1;

  execute(0x3404);

  ASSERT_EQ(3, memory.PC);
}

TEST_F(executor_test, 3_SE_skip_next_instruction_if_Vx_eq_kk_false) {
  memory.PC = 1;

  execute(0x3456);

  ASSERT_EQ(1, memory.PC);
}

TEST_F(executor_test, 4_SNE_skip_next_instruction_if_Vx_neq_kk_true) {
  memory.PC = 1;

  execute(0x4456);

  ASSERT_EQ(3, memory.PC);
}

TEST_F(executor_test, 4_SNE_skip_next_instruction_if_Vx_neq_kk_false) {
  memory.PC = 1;

  execute(0x4505);

  ASSERT_EQ(1, memory.PC);
}

TEST_F(executor_test, 5_SE_skip_next_instruction_if_Vx_eq_Vy_true) {
  memory.PC = 1;
  memory.V[4] = 0x5;

  execute(0x5450);

  ASSERT_EQ(3, memory.PC);
}

TEST_F(executor_test, 5_SE_skip_next_instruction_if_Vx_eq_Vy_false) {
  memory.PC = 1;

  execute(0x5450);

  ASSERT_EQ(1, memory.PC);
}

TEST_F(executor_test, 6_LD_set_Vx_to_kk) {
  execute(0x6323);

  ASSERT_EQ(0x23, memory.V[3]);
}

TEST_F(executor_test, 7_ADD_set_Vx_to_Vx_plus_kk) {
  execute(0x7723);

  ASSERT_EQ(0x2A, memory.V[7]);
}

TEST_F(executor_test, 8_LD_set_Vx_to_Vy) {
  execute(0x8670);

  ASSERT_EQ(0x7, memory.V[6]);
}

TEST_F(executor_test, 8_OR_set_Vx_to_Vx_or_Vy) {
  execute(0x8141);

  ASSERT_EQ(0x5, memory.V[1]);
}

TEST_F(executor_test, 8_AND_set_Vx_to_Vx_and_Vy) {
  execute(0x8542);

  ASSERT_EQ(0x4, memory.V[5]);
}

TEST_F(executor_test, 8_XOR_set_Vx_to_Vx_xor_Vy) {
  execute(0x8543);

  ASSERT_EQ(0x1, memory.V[5]);
}

TEST_F(executor_test, 8_ADD_set_Vx_to_Vx_plus_Vy_set_VF_to_carry_0) {
  execute(0x8AB4);

  ASSERT_EQ(0x15, memory.V[0xA]);
  ASSERT_EQ(0x0, memory.VF);
}

TEST_F(executor_test, 8_ADD_set_Vx_to_Vx_plus_Vy_set_VF_to_carry_1) {
  memory.V[0xA] = 0xFF;

  execute(0x8AB4);

  ASSERT_EQ(0xA, memory.V[0xA]);
  ASSERT_EQ(0x1, memory.VF);
}

TEST_F(executor_test, 8_SUB_set_Vx_to_Vx_minux_Vy_set_VF_to_carry_1) {
  execute(0x8545);

  ASSERT_EQ(0x1, memory.V[5]);
  ASSERT_EQ(0x1, memory.VF);
}

TEST_F(executor_test, 8_SUB_set_Vx_to_Vx_minux_Vy_set_VF_to_carry_0) {
  execute(0x8455);

  ASSERT_EQ(0xFF, memory.V[4]);
  ASSERT_EQ(0x0, memory.VF);
}

TEST_F(executor_test, 8_SHR_set_Vx_to_Vx_SHR_1_and_VF_0) {
  execute(0x8456);

  ASSERT_EQ(2, memory.V[4]);
  ASSERT_EQ(0, memory.VF);
}

TEST_F(executor_test, 8_SHR_set_Vx_to_Vx_SHR_1_and_VF_1) {
  execute(0x8356);

  ASSERT_EQ(1, memory.V[3]);
  ASSERT_EQ(1, memory.VF);
}

TEST_F(executor_test, 8_SUBN_set_Vx_to_Vy_minus_Vx_set_VF_Not_bottow_0) {
  execute(0x8547);

  ASSERT_EQ(0x1, memory.V[5]);
  ASSERT_EQ(0, memory.VF);
}

TEST_F(executor_test, 8_SUBN_set_Vx_to_Vy_minus_Vx_set_VF_Not_bottow_1) {
  execute(0x8457);

  ASSERT_EQ(0xFF, memory.V[4]);
  ASSERT_EQ(1, memory.VF);
}

TEST_F(executor_test, 8_SHL_set_Vx_to_Vx_SHL_1_0) {
  execute(0x887E);

  ASSERT_EQ(0x10, memory.V[8]);
  ASSERT_EQ(0, memory.VF);
}

TEST_F(executor_test, 8_SHL_set_Vx_to_Vx_SHL_1_1) {
  memory.V[8] = 0xF0;

  execute(0x887E);

  ASSERT_EQ(0xE0, memory.V[8]);
  ASSERT_EQ(1, memory.VF);
}

TEST_F(executor_test, 9_SNE_skip_next_instruction_if_Vx_neq_Vy_true) {
  execute(0x9450);

  ASSERT_EQ(0x2, memory.PC);
}

TEST_F(executor_test, 9_SNE_skip_next_instruction_if_Vx_neq_Vy_false) {
  execute(0x9440);

  ASSERT_EQ(0x0, memory.PC);
}

TEST_F(executor_test, A_LD_set_I_to_nnn) {
  execute(0xA123);

  ASSERT_EQ(0x123, memory.I);
}

TEST_F(executor_test, B_JP_jump_to_location_nnn_plus_V0) {
  memory.V[0] = 5;

  execute(0xB123);

  ASSERT_EQ(0x128, memory.PC);
}

TEST_F(executor_test, C_RND_set_Vx_to_random_byte_AND_kk) {
  execute(0xC500);

  ASSERT_EQ(0x0, memory.V[5]);
}

TEST_F(executor_test, D_DRW_display_n_byte_sprite_TODO) {
  execute(0xD58A);

  EXPECT_TRUE(false);
}

TEST_F(executor_test, E_SKP_skip_next_instruction_if_key_with_value_f_Vx_is_pressed_false) {
  execute(0xE59E);

  EXPECT_EQ(0, memory.PC);
}

TEST_F(executor_test, E_SKP_skip_next_instruction_if_key_with_value_f_Vx_is_pressed_true) {
  memory.Keypad[5] = 1;

  execute(0xE59E);

  EXPECT_EQ(2, memory.PC);
}

TEST_F(executor_test, E_SKNP_skip_next_instruction_if_key_with_value_f_Vx_is_not_pressed_false) {
  memory.Keypad[5] = 1;

  execute(0xE5A1);

  EXPECT_EQ(0, memory.PC);
}

TEST_F(executor_test, E_SKNP_skip_next_instruction_if_key_with_value_f_Vx_is_not_pressed_true) {
  execute(0xE5A1);

  EXPECT_EQ(2, memory.PC);
}

TEST_F(executor_test, F_LD_set_Vx_to_delay_timer_value) {
  memory.DT = 0xA;

  execute(0xFE07);

  EXPECT_EQ(0xA, memory.V[0xE]);
}

TEST_F(executor_test, F_LD_wait_for_a_key_press_store_the_value_of_the_key_in_Vx) {
  execute(0xF20A);

  EXPECT_TRUE(false);
}

TEST_F(executor_test, F_LD_set_delay_timer_to_Vx) {
  memory.V[7] = 0xB;

  execute(0xF715);

  EXPECT_EQ(0xB, memory.DT);
}

TEST_F(executor_test, F_LD_set_sound_timer_to_Vx) {
  memory.V[7] = 0xB;

  execute(0xF718);

  EXPECT_EQ(0xB, memory.ST);
}

TEST_F(executor_test, F_ADD_set_I_to_I_add_Vx) {
  memory.I = 2;
  memory.V[3] = 5;

  execute(0xF31E);

  EXPECT_EQ(7, memory.I);
}

TEST_F(executor_test, F_LD_set_I_to_location_of_sprite_for_digit_Vx) {
  execute(0xFB29);

  EXPECT_TRUE(false);
}

TEST_F(executor_test, F_LD_store_BCD_representation_of_Vx_in_memory_location_I) {
  execute(0xF933);

  EXPECT_TRUE(false);
}

TEST_F(executor_test, F_LD_store_registers_V0_through_Vx_in_memory_starting_at_location_I) {
  execute(0xFB55);

  EXPECT_TRUE(false);
}

TEST_F(executor_test, F_LD_read_registers_Vo_throu_Vx_from_memory_starting_at_location_I) {
  execute(0xFE65);

  EXPECT_TRUE(false);
}

