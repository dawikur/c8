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

#include "callbacks.hpp"
#include "gui/debugform.hpp"
#include "gui/display.hpp"
#include "gui/menubar.hpp"
#include "type.hpp"

namespace gui {

class IconInit {
  public:
    IconInit();
};

class C8form : public IconInit, public nana::form {
 public:
  explicit C8form(Byte const *const display);

  void exec();

  void fileChoosen(FileChoosen const &callback);
  void clockChoosen(ClockChoosen const &callback);
  void keyEvent(KeyEvent const &callback);

  UpdateDisplay updateDisplayCallback();

 private:
  void createMenubar();

  void connectToKeyboardEvents();
  void connectToDragDropEvents();

  void keyboardEvent(nana::arg_keyboard const &, Byte const);

  FileChoosen _fileChoosen;
  KeyEvent _keyEvent;

  Menubar _menubar;
  Display _display;
  Debugform _debug;
};

}  // namespace gui

#endif  // INCLUDE_GUI_C8FORM_HPP_
