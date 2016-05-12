// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/c8form.hpp"

#include <string>

#include <nana/gui/filebox.hpp>

namespace gui {

C8form::C8form(Byte const *const display)
  : nana::form{}
  , _menubar{*this}
  , _fileChoosen{[](std::string const &) {}}
  , _keyEvent{[](char const, bool const) {}}
  , _display{display, *this} {
  caption("c8");
  bgcolor(nana::colors::white);

  createMenubar();
  connectToKeyboardEvents();
  connectToDragDropEvents();
}

void C8form::exec() {
  show();
  nana::exec();
}

void C8form::fileChoosen(FileChoosen const &callback) {
  _fileChoosen = callback;
}

void C8form::keyEvent(KeyEvent const &callback) {
  _keyEvent = callback;
}

void C8form::createMenubar() {
  _menubar.bgcolor(nana::colors::white);

  auto &fileMenu = _menubar.push_back("File");
  fileMenu.append("Open",
                  [this](nana::menu::item_proxy &) {
                    nana::filebox filebox{*this, true};
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
                          _display.theme(nana::colors::black, nana::colors::white);
                        });
  viewThemeMenu->append("Dark",
                        [=](nana::menu::item_proxy &) {
                          _display.theme(nana::colors::white, nana::colors::black);
                        });
  viewThemeMenu->append("Matrix",
                        [=](nana::menu::item_proxy &) {
                          _display.theme(nana::colors::green, nana::colors::black);
                        });
  viewThemeMenu->check_style(0, nana::menu::checks::option);
  viewThemeMenu->check_style(1, nana::menu::checks::option);
  viewThemeMenu->check_style(2, nana::menu::checks::option);
  viewThemeMenu->checked(0, true);

  auto &helpMenu = _menubar.push_back("Help");
  helpMenu.append("About",
                  [this](nana::menu::item_proxy &) {
                    auto msgbox = nana::msgbox{*this, "About c8"}.icon(
                      nana::msgbox::icon_information);
                    msgbox << "Chip8 - interpreter";
                    msgbox.show();
                  });
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
