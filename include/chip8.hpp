// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP8_HPP_
#define INCLUDE_CHIP8_HPP_

#include <atomic>
#include <string>
#include <thread>

#include "executor.hpp"
#include "memory.hpp"
#include "opcode.hpp"

class Chip8 {
 public:
  explicit Chip8(Byte const &clock = 60);
  ~Chip8();

  void load(std::string const &file);

  void run();

 private:
  void start();
  void stop();
  void main();

  void tick();
  void wait();

  using Duration = std::chrono::duration<double>;
  Duration cycleDuration;

  Memory memory;
  Opcode command;
  Executor execute;

  std::atomic_bool running;
  std::thread worker;
};

#endif  // INCLUDE_CHIP8_HPP_
