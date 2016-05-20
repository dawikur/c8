// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_CALLBACKS_HPP_
#define INCLUDE_CALLBACKS_HPP_

#include <functional>
#include <string>

#include "type.hpp"

using ClockChoosen = std::function<void(unsigned const)>;
using DebugChoosen = std::function<void()>;
using FileChoosen = std::function<void(std::string const &)>;
using GetKey = std::function<Byte()>;
using KeyEvent = std::function<void(wchar_t const key, Byte const isPressed)>;
using Redraw = std::function<void()>;
using UpdateDisplay = std::function<void()>;

#endif  // INCLUDE_CALLBACKS_HPP_

