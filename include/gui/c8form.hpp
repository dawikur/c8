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

#include "gui/display.hpp"
#include "type.hpp"

namespace gui {

class C8form : public nana::form {
 public:
  using FileChoosen = std::function<void (std::string const&)>;
  using Redraw = std::function<void ()>;

  explicit C8form(Byte const *const display);

  void exec();

  void fileChoosen(FileChoosen const &callback);

  Redraw redrawCallback();

 private:
  void createMenubar();

  nana::menubar _menubar;
  FileChoosen _fileChoosen;

  Display _display;
};

}  // namespace gui

#endif  // INCLUDE_GUI_C8FORM_HPP_
