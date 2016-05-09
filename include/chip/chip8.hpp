// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP_CHIP8_HPP_
#define INCLUDE_CHIP_CHIP8_HPP_

#include <atomic>
#include <string>
#include <thread>

#include "executor.hpp"
#include "memory.hpp"

namespace chip {

class Chip8 {
 public:
  using GetKey = Executor::GetKey;
  using Redraw = std::function<void ()>;

  using FileChoosen = std::function<void(std::string const &)>;

  explicit Chip8(Byte const &clock = 60);
  ~Chip8();

  void getKey(GetKey const &callback);
  void redraw(Redraw const &callback);

  FileChoosen fileChoosenCallback();

  Byte const *const getDisplay();

 private:
  void load(std::string const &);
  void start();
  void stop();
  void main();

  Word fetch();
  void tick();
  void wait();

  using Duration = std::chrono::milliseconds;
  Duration _cycleDuration;

  Memory _memory;
  Executor _execute;
  GetKey _getKey;
  Redraw _redraw;

  std::atomic_bool _running;
  std::thread _worker;
};

}  // namespace chip

#endif  // INCLUDE_CHIP_CHIP8_HPP_
