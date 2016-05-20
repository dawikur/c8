// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/c8form.hpp"

#include <string>

#include <nana/paint/image.hpp>

namespace gui {

IconInit::IconInit() {
#ifdef _WIN32
  nana::API::window_icon_default(nana::paint::image{"c8.exe"});
#endif
}

C8form::C8form(Byte const *const display)
  : IconInit{}
  , nana::form{}
  , _fileChoosen{}
  , _keyEvent{}
  , _menubar{*this}
  , _display{display, *this}
  , _debug{} {
  caption("c8");
  bgcolor(nana::colors::white);

  connectToKeyboardEvents();
  connectToDragDropEvents();

  _menubar.debugChoosen([this]() { _debug.run(); });
  _menubar.scaleChoosen([this](size_t const scale) { _display.scale(scale); });
  _menubar.themeChoosen([this](nana::color const fg, nana::color const bg) {
    _display.theme(fg, bg);
  });
}

void C8form::exec() {
  show();
  nana::exec();
}

void C8form::fileChoosen(FileChoosen const &callback) {
  _fileChoosen = callback;
  _menubar.fileChoosen(callback);
}

void C8form::clockChoosen(ClockChoosen const &callback) {
  _menubar.clockChoosen(callback);
}

void C8form::keyEvent(KeyEvent const &callback) {
  _keyEvent = callback;
}

UpdateDisplay C8form::updateDisplayCallback() {
  return _display.updateCallback();
}

void C8form::connectToKeyboardEvents() {
  events().key_press(
    [this](nana::arg_keyboard const &arg) { keyboardEvent(arg, 0x01); });

  events().key_release(
    [this](nana::arg_keyboard const &arg) { keyboardEvent(arg, 0x00); });
}

void C8form::connectToDragDropEvents() {
  enable_dropfiles(true);
  events().mouse_dropfiles([this](nana::arg_dropfiles const &arg) {
    _fileChoosen(arg.files.front());
  });
}

void C8form::keyboardEvent(nana::arg_keyboard const &arg,
                           Byte const isPressed) {
  _keyEvent(arg.key, isPressed);
}

}  // namespace gui
