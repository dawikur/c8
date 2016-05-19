// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/menubar.hpp"

#ifdef _WIN32
# include <windows.h>
#endif

#include <nana/gui/filebox.hpp>

namespace gui {

Menubar::Menubar(nana::form const &form)
  : _clockChoosen{}
  , _debugChoosen{}
  , _fileChoosen{}
  , _scaleChoosen{}
  , _themeChoosen{}
  , _form{form}
  , _menubar{_form} {
  createMenubar();
}

void Menubar::clockChoosen(ClockChoosen const &callback) {
  _clockChoosen = callback;
}

void Menubar::debugChoosen(DebugChoosen const &callback) {
  _debugChoosen = callback;
}

void Menubar::fileChoosen(FileChoosen const &callback) {
  _fileChoosen = callback;
}

void Menubar::scaleChoosen(ScaleChoosen const &callback) {
  _scaleChoosen = callback;
}

void Menubar::themeChoosen(ThemeChoosen const &callback) {
  _themeChoosen = callback;
}

void Menubar::createMenubar() {
  _menubar.bgcolor(nana::colors::white);

  createFileMenu();
  createViewMenu();
  createSettingsMenu();
  createHelpMenu();
}

void Menubar::createFileMenu() {
  auto &menu = _menubar.push_back("File");
  menu.append("Open", [this](auto &) { this->openFile(); });
  menu.append_splitter();
  menu.append("Exit", [](auto &) { nana::API::exit(); });
}

void Menubar::createViewMenu() {
  auto &menu = _menubar.push_back("View");
  createThemeViewMenu(menu, 0);
  createScaleViewMenu(menu, 1);

  menu.append_splitter();
  menu.append("Debug", [=](auto &) { _debugChoosen(); });
}

void Menubar::createThemeViewMenu(nana::menu &menu, size_t const id) {
  using nana::colors;

  menu.append("Theme");
  auto *themeMenu = menu.create_sub_menu(id);

  themeMenu->append(
    "Light", [=](auto &) { _themeChoosen(colors::black, colors::white); });
  themeMenu->append(
    "Dark", [=](auto &) { _themeChoosen(colors::white, colors::black); });
  themeMenu->append(
    "Matrix", [=](auto &) { _themeChoosen(colors::lime, colors::black); });

  for (size_t i = 0; i < themeMenu->size(); ++i) {
    themeMenu->check_style(i, nana::menu::checks::option);
  }
  themeMenu->checked(0, true);
}

void Menubar::createScaleViewMenu(nana::menu &menu, size_t const id) {
  menu.append("Scale");
  auto *scaleMenu = menu.create_sub_menu(id);

  scaleMenu->append("x1", [=](auto &) { _scaleChoosen(1); });
  scaleMenu->append("x2", [=](auto &) { _scaleChoosen(2); });
  scaleMenu->append("x3", [=](auto &) { _scaleChoosen(3); });
  scaleMenu->append("x4", [=](auto &) { _scaleChoosen(4); });

  for (size_t i = 0; i < scaleMenu->size(); ++i) {
    scaleMenu->check_style(i, nana::menu::checks::option);
  }
  scaleMenu->checked(0, true);
}

void Menubar::createSettingsMenu() {
  auto &menu = _menubar.push_back("Settings");
  createClockSettingsMenu(menu);
}

void Menubar::createClockSettingsMenu(nana::menu &menu) {
  menu.append("Clock");
  auto *clockMenu = menu.create_sub_menu(0);

  clockMenu->append("64Hz", [=](auto &) { _clockChoosen(64); });
  clockMenu->append("128Hz", [=](auto &) { _clockChoosen(128); });
  clockMenu->append("256Hz", [=](auto &) { _clockChoosen(256); });
  clockMenu->append("512Hz", [=](auto &) { _clockChoosen(512); });
  clockMenu->append("1024Hz", [=](auto &) { _clockChoosen(1024); });

  for (size_t i = 0; i < clockMenu->size(); ++i) {
    clockMenu->check_style(i, nana::menu::checks::option);
  }
  clockMenu->checked(2, true);
}

void Menubar::createHelpMenu() {
  auto &menu = _menubar.push_back("Help");

#ifdef __linux__
  menu.append("Home page", [](auto &) {
    system("xdg-open http://github.com/dawikur/c8"); });
#elif _WIN32
  menu.append("Home page", [](auto &) {
    ::ShellExecuteA(
      NULL, "open", "http://github.com/dawikur/c8", NULL, NULL, SW_SHOWNORMAL);
  });
#endif

  menu.append_splitter();
  menu.append("About", [this](auto &) { this->showAbout(); });
}

void Menubar::openFile() {
  nana::filebox filebox{_form, true};
  filebox.add_filter("Rom File (*.rom)", "*.rom");
  filebox.add_filter("c8rom File (*.c8rom)", "*.c8rom");
  filebox.add_filter("All Files (*.*)", "*.*");

  if (filebox()) {
    _fileChoosen(filebox.file());
  }
}

void Menubar::showAbout() {
  auto msgbox =
    nana::msgbox{_form, "c8 - about"}.icon(nana::msgbox::icon_information);
  msgbox << "Chip8 - interpreter";
  msgbox.show();
}

}  // namespace gui
