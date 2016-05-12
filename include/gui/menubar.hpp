// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_MENUBAR_HPP_
#define INCLUDE_GUI_MENUBAR_HPP_

#include <functional>
#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <vector>                                                              // fix for nana

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

#include "callbacks.hpp"
#include "type.hpp"

namespace gui {

using ThemeChoosen =
  std::function<void(nana::color const fg, nana::color const bg)>;

class Menubar {
 public:
  explicit Menubar(nana::form const &form);

  void fileChoosen(FileChoosen const &callback);
  void themeChoosen(ThemeChoosen const &callback);

 private:
  void createMenubar();

  FileChoosen _fileChoosen;
  ThemeChoosen _themeChoosen;

  nana::form const &_form;
  nana::menubar _menubar;
};

}  // namespace gui

#endif  // INCLUDE_GUI_MENUBAR_HPP_

