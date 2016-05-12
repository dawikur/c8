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

  auto &fileMenu = _menubar.push_back("File");
  fileMenu.append("Open",
                  [this](nana::menu::item_proxy &) {
                    nana::filebox filebox{_form, true};
                    filebox.add_filter("Rom File (*.rom)", "*.rom");
                    filebox.add_filter("c8rom File (*.c8rom)", "*.c8rom");
                    filebox.add_filter("All Files (*.*)", "*.*");

                    if (filebox()) {
                      _fileChoosen(filebox.file());
                    }
                  });
  fileMenu.append_splitter();
  fileMenu.append("Exit", [](nana::menu::item_proxy &) { nana::API::exit(); });

  auto &viewMenu = _menubar.push_back("View");
  viewMenu.append("Theme");
  auto *viewThemeMenu = viewMenu.create_sub_menu(0);
  viewThemeMenu->append("Light",
                        [=](nana::menu::item_proxy &) {
                          _themeChoosen(nana::colors::black, nana::colors::white);
                        });
  viewThemeMenu->append("Dark",
                        [=](nana::menu::item_proxy &) {
                          _themeChoosen(nana::colors::white, nana::colors::black);
                        });
  viewThemeMenu->append("Matrix",
                        [=](nana::menu::item_proxy &) {
                          _themeChoosen(nana::colors::green, nana::colors::black);
                        });
  viewThemeMenu->check_style(0, nana::menu::checks::option);
  viewThemeMenu->check_style(1, nana::menu::checks::option);
  viewThemeMenu->check_style(2, nana::menu::checks::option);
  viewThemeMenu->checked(0, true);

  auto &helpMenu = _menubar.push_back("Help");
  helpMenu.append("About",
                  [this](nana::menu::item_proxy &) {
                    auto msgbox = nana::msgbox{_form, "About c8"}.icon(
                      nana::msgbox::icon_information);
                    msgbox << "Chip8 - interpreter";
                    msgbox.show();
                  });
}

}  // namespace gui
