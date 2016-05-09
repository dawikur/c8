// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_C8FORM_HPP_
#define INCLUDE_GUI_C8FORM_HPP_

#include <functional>
#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <string>
#include <vector>                                                              // fix dor nana

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

#include "callbacks.hpp"
#include "gui/display.hpp"
#include "type.hpp"

namespace gui {

class C8form : public nana::form {
 public:
  explicit C8form(Byte const *const display);

  void exec();

  void fileChoosen(FileChoosen const &callback);
  void keyEvent(KeyEvent const &callback);

  Redraw redrawCallback();

 private:
  void createMenubar();
  void connectToKeyboardEvents();
  void keyboardEvent(nana::arg_keyboard const &, Byte const);

  nana::menubar _menubar;
  FileChoosen _fileChoosen;
  KeyEvent _keyEvent;

  Display _display;
};

}  // namespace gui

#endif  // INCLUDE_GUI_C8FORM_HPP_
