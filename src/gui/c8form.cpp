// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/c8form.hpp"

#include <string>

namespace gui {

C8form::C8form(Byte const *const display)
  : nana::form{}
  , _fileChoosen{}
  , _keyEvent{}
  , _menubar{*this}
  , _display{display, *this} {
  caption("c8");
  bgcolor(nana::colors::white);

  connectToKeyboardEvents();
  connectToDragDropEvents();

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

void C8form::connectToKeyboardEvents() {
  events().key_press(
    [this](nana::arg_keyboard const &arg) { keyboardEvent(arg, 0x01); });

  events().key_release(
    [this](nana::arg_keyboard const &arg) { keyboardEvent(arg, 0x00); });
}

void C8form::connectToDragDropEvents() {
  events().mouse_dropfiles([this](nana::arg_dropfiles const &arg) {
    _fileChoosen(arg.files.front());
  });
}

void C8form::keyboardEvent(nana::arg_keyboard const &arg,
                           Byte const isPressed) {
  _keyEvent(arg.key, isPressed);
}

}  // namespace gui
