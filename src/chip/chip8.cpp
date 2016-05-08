// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "chip/chip8.hpp"

#include <atomic>
#include <fstream>
#include <stdexcept>
#include <string>
#include <thread>

#include "chip/executor.hpp"
#include "chip/memory.hpp"
#include "chip/opcode.hpp"

namespace chip {

Chip8::Chip8(Byte const &clock)
  : _cycleDuration{1000 / clock}
  , _memory{}
  , _execute{}
  , _running{false}
  , _worker{} {}

Chip8::~Chip8() {
  stop();
}

void Chip8::load(std::string const &file) {
  stop();

  size_t position = 0x200;
  for (std::ifstream input{file, std::ios::binary}; input.good();) {
    if (position > 0x1000) {
      throw std::runtime_error{"Input file is too big, max size is " +
                               std::to_string(0x1000 - 0x200)};
    }

    _memory.Raw[position++] = input.get();
  }

  start();
}

void Chip8::getKey(GetKey const &callback) {
  _getKey = callback;
}

Byte* Chip8::getDisplay() {
  return _memory.Display;
}

void Chip8::start() {
  _running = true;
  _memory.PC = 0x200;
  _worker = std::thread{&Chip8::main, this};
}

void Chip8::stop() {
  _running = false;
  if (_worker.joinable()) {
    _worker.join();
  }
}

void Chip8::main() {
  while (_running) {
    Opcode const command{_memory.Raw[_memory.PC]};
    _execute(command, _memory, _getKey);

    tick();
    wait();
  }
}

void Chip8::tick() {
  ++_memory.PC;
  if (_memory.ST > 0) {
    --_memory.ST;
  }
  if (_memory.DT > 0) {
    --_memory.DT;
  }
}

void Chip8::wait() {
  std::this_thread::sleep_for(std::chrono::milliseconds(166));
}

}  // namespace chip
