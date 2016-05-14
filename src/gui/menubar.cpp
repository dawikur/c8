// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/menubar.hpp"

#include <nana/gui/filebox.hpp>

namespace gui {

Menubar::Menubar(nana::form const &form)
  : _fileChoosen{}, _themeChoosen{}, _form{form}, _menubar{_form} {
  createMenubar();
}

void Menubar::fileChoosen(FileChoosen const &callback) {
  _fileChoosen = callback;
}

void Menubar::themeChoosen(ThemeChoosen const &callback) {
  _themeChoosen = callback;
}

void Menubar::createMenubar() {
  _menubar.bgcolor(nana::colors::white);

  createFileMenu();
  createViewMenu();
  createHelpMenu();
}

void Menubar::createFileMenu() {
  auto &menu = _menubar.push_back("File");
  menu.append("Open", [this](auto &) { openFile(); });
  menu.append_splitter();
  menu.append("Exit", [](auto &) { nana::API::exit(); });
}

void Menubar::createViewMenu() {
  using nana::colors;

  auto &menu = _menubar.push_back("View");
  menu.append("Theme");
  auto *themeMenu = menu.create_sub_menu(0);

  themeMenu->append(
    "Light", [=](auto &) { _themeChoosen(colors::black, colors::white); });
  themeMenu->append(
    "Dark", [=](auto &) { _themeChoosen(colors::white, colors::black); });
  themeMenu->append(
    "Matrix", [=](auto &) { _themeChoosen(colors::lime, colors::black); });

  themeMenu->check_style(0, nana::menu::checks::option);
  themeMenu->check_style(1, nana::menu::checks::option);
  themeMenu->check_style(2, nana::menu::checks::option);

  themeMenu->checked(0, true);
}

void Menubar::createSettingsMenu() {
  auto &menu = _menubar.push_back("Settings");
  menu.append("Clock");
  auto *clockMenu = menu.create_sub_menu(0);

}

void Menubar::createHelpMenu() {
  auto &menu = _menubar.push_back("Help");
  menu.append("About", [this](auto &) { showAbout(); });
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
    nana::msgbox{_form, "About c8"}.icon(nana::msgbox::icon_information);
  msgbox << "Chip8 - interpreter";
  msgbox.show();
}

}  // namespace gui
