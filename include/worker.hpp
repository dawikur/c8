// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_WORKER_HPP_
#define INCLUDE_WORKER_HPP_

#include <atomic>
#include <chrono>
#include <thread>

class Worker {
 public:
  Worker(unsigned const clock) : _cycleDuration{}, _running{false}, _thread{} {
    setClock(clock);
  }

  ~Worker() { stop(); }

 protected:
  virtual void do_one() = 0;

  void start() {
    _running = true;
    _thread = std::thread{&Worker::main, this};
  }

  void stop() {
    _running = false;
    if (_thread.joinable()) {
      _thread.join();
    }
  }

  void setClock(unsigned const clock) {
    _cycleDuration = std::chrono::milliseconds{1000 / clock};
  }

 private:
  void main() {
    while (_running) {
      auto const begin = std::chrono::system_clock::now();

      do_one();

      auto const end = std::chrono::system_clock::now();
      std::this_thread::sleep_for(_cycleDuration.load() - (end - begin));
    }
  }

  std::atomic<std::chrono::milliseconds> _cycleDuration;
  std::atomic_bool _running;
  std::thread _thread;
};

#endif  // INCLUDE_WORKER_HPP_

