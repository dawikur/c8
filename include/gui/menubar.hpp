// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_MENUBAR_HPP_
#define INCLUDE_GUI_MENUBAR_HPP_

#include <functional>
#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <string>
#include <vector>                                                              // fix for nana

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

#include "callbacks.hpp"
#include "type.hpp"

namespace gui {

using ThemeChoosen =
  std::function<void(nana::color const fg, nana::color const bg)>;
using ScaleChoosen = std::function<void(size_t const)>;

class Menubar {
 public:
  explicit Menubar(nana::form const &form);

  void clockChoosen(ClockChoosen const &callback);
  void debugChoosen(DebugChoosen const &callback);
  void fileChoosen(FileChoosen const &callback);
  void scaleChoosen(ScaleChoosen const &callback);
  void themeChoosen(ThemeChoosen const &callback);

 private:
  void createMenubar();
  void createFileMenu();
  void createViewMenu();
  void createThemeViewMenu(nana::menu &, size_t const);
  void createScaleViewMenu(nana::menu &, size_t const);
  void createSettingsMenu();
  void createClockSettingsMenu(nana::menu &);
  void createHelpMenu();

  void openFile();
  void showAbout();

  template <typename Callback, class... Args>
  void addRadioButton(nana::menu *dst,
                      std::string const &name,
                      Callback const &callback,
                      Args const &... args) {
    dst->append(name, [=](auto &) { callback(args...); });
    dst->check_style(dst->size() - 1, nana::menu::checks::option);
  }

  ClockChoosen _clockChoosen;
  DebugChoosen _debugChoosen;
  FileChoosen _fileChoosen;
  ScaleChoosen _scaleChoosen;
  ThemeChoosen _themeChoosen;

  nana::form const &_form;
  nana::menubar _menubar;
};

}  // namespace gui

#endif  // INCLUDE_GUI_MENUBAR_HPP_

