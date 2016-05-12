// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CHIP_CHIP8_HPP_
#define INCLUDE_CHIP_CHIP8_HPP_

#include <string>

#include "callbacks.hpp"
#include "chip/executor.hpp"
#include "chip/memory.hpp"
#include "worker.hpp"

namespace chip {

class Chip8 : public Worker {
 public:
  explicit Chip8(unsigned const clock = 256);

  void getKey(GetKey const &callback);

  FileChoosen fileChoosenCallback();
  KeyEvent keyEventCallback();

  Byte const *const getDisplay();

 private:
  void initFont();
  void load(std::string const &);
  void keyEvent(wchar_t const key, Byte const isPressed);

  size_t filesize(std::string const&);
  void do_one() override;

  Word fetch();
  void tick();

  Memory _memory;
  Executor _execute;
  GetKey _getKey;
};

}  // namespace chip

#endif  // INCLUDE_CHIP_CHIP8_HPP_
