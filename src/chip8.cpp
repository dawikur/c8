// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "chip8.hpp"

#include <atomic>
#include <fstream>
#include <stdexcept>
#include <string>
#include <thread>

#include "executor.hpp"
#include "memory.hpp"
#include "opcode.hpp"

Chip8::Chip8()
  : memory{}, command{}, execute{}, running{false}, worker{} {}

Chip8::~Chip8() {
  stop();
}

void Chip8::load(std::string const &file) {
  size_t position = 0x200;
  for (std::ifstream input{file, std::ios::binary}; input.good();) {
    if (position > 0x1000) {
      throw std::runtime_error{"Input file is too big, max size is " +
                               std::to_string(0x1000 - 0x200)};
    }

    memory.Raw[position++] = input.get();
  }

  run();
}

void Chip8::run() {
  stop();
  start();
}

void Chip8::start() {
  running = true;
  worker = std::thread{&Chip8::main, this};
}

void Chip8::stop() {
  running = false;
  if (worker.joinable()) {
    worker.join();
  }
}

void Chip8::main() {
  while (running) {
    execute(command, memory);
  }
}
