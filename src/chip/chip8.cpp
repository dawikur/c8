// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "chip/chip8.hpp"

#include <atomic>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <thread>

#include "chip/executor.hpp"
#include "chip/memory.hpp"
#include "chip/opcode.hpp"

namespace chip {

Chip8::Chip8(unsigned const clock)
  : Worker{clock}, _memory{}, _execute{}, _getKey{[]() { return 0; }} {
  initFont();
}

void Chip8::getKey(GetKey const &callback) {
  _getKey = callback;
}

FileChoosen Chip8::fileChoosenCallback() {
  return [this](std::string const &file) { load(file); };
}

ClockChoosen Chip8::clockChoosenCallback() {
  return [this](unsigned const clock) { setClock(clock); };
}

KeyEvent Chip8::keyEventCallback() {
  return
    [this](wchar_t const key, Byte const isPressed) { keyEvent(key, isPressed); };
}

Byte const *const Chip8::getDisplay() {
  return _memory.Display;
}

void Chip8::initFont() {
  auto* p = _memory.Font;
  for (auto f : {0xF999F,
                 0x72262,
                 0xF8F1F,
                 0xF1F1F,
                 0x11F99,
                 0xF1F8F,
                 0xF9F8F,
                 0x4421F,
                 0xF9F9F,
                 0xF1F9F,
                 0x99F9F,
                 0xE9E9E,
                 0xF888F,
                 0xE999E,
                 0xF8F8F,
                 0x88F8F}) {
    for (auto i = 0; i < 5; ++i) {
      *p = (f & 0xF) << 4;
      ++p;
      f >>= 4;
    }
  }
}

void Chip8::load(std::string const &file) {
  stop();

  if (filesize(file) > 0x1000) {
    throw std::runtime_error{"Input file is too big, max size is 0x800"};
  }

  size_t position = 0x200;
  for (std::ifstream input{file, std::ios::binary}; input.good();) {
    _memory.Raw[position++] = input.get();
  }

  _execute(Opcode{0x00E0}, _memory, _getKey);
  _memory.PC = 0x200;

  start();
}

void Chip8::keyEvent(wchar_t const key, Byte const isPressed) {
  static std::map<wchar_t, int> keyRemap = {
    {L'1', 0x1}, {L'2', 0x2}, {L'3', 0x3}, {L'4', 0xC},
    {L'Q', 0x4}, {L'W', 0x5}, {L'E', 0x6}, {L'R', 0xD},
    {L'A', 0x7}, {L'S', 0x8}, {L'D', 0x9}, {L'F', 0xE},
    {L'Z', 0xA}, {L'X', 0x0}, {L'C', 0xB}, {L'V', 0xF}
  };

  if (keyRemap.find(key) == keyRemap.end()) {
    return;
  }

  _memory.Keypad[keyRemap[key]] = isPressed;
}

size_t Chip8::filesize(std::string const& file) {
  std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
  return static_cast<size_t>(in.tellg());
}

void Chip8::do_one() {
  auto const opcode = fetch();
  _execute(Opcode{opcode}, _memory, _getKey);
  tick();
}

Word Chip8::fetch() {
  Word opcode = _memory.Raw[_memory.PC++] << 8;
  opcode |= _memory.Raw[_memory.PC++];
  return opcode;
}

void Chip8::tick() {
  if (_memory.ST > 1) {
    --_memory.ST;
  }
  if (_memory.DT > 0) {
    --_memory.DT;
  }
}

}  // namespace chip
