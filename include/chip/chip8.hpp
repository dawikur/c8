// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP_CHIP8_HPP_
#define INCLUDE_CHIP_CHIP8_HPP_

#include <atomic>
#include <string>
#include <thread>

#include "executor.hpp"
#include "memory.hpp"
#include "opcode.hpp"

namespace chip {

class Chip8 {
 public:
  using GetKey = Executor::GetKey;

  explicit Chip8(Byte const &clock = 60);
  ~Chip8();

  void load(std::string const &file);
  void getKey(GetKey const &callback);

 private:
  void start();
  void stop();
  void main();

  void tick();
  void wait();

  using Duration = std::chrono::milliseconds;
  Duration cycleDuration;

  Memory memory;
  Opcode command;
  Executor execute;
  GetKey getKeyCallback;

  std::atomic_bool running;
  std::thread worker;
};

}  // namespace chip

#endif  // INCLUDE_CHIP_CHIP8_HPP_
