// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/c8form.hpp"

#include <string>

#include <nana/gui/filebox.hpp>

namespace gui {

C8form::C8form(Byte *display)
  : nana::form{}
  , _menubar{*this}
  , _fileChoosen{[](std::string const &) {}}
  , _display{display, *this} {
  caption("c8");
  bgcolor(nana::colors::white);

  createMenubar();
}

void C8form::exec() {
  show();
  nana::exec();
}

void C8form::fileChoosen(FileChoosen const &callback) {
  _fileChoosen = callback;
}

void C8form::createMenubar() {
  _menubar.bgcolor(nana::colors::white);

  auto& fileMenu = _menubar.push_back("File");
  fileMenu.append("Open", [this](nana::menu::item_proxy&) {
      nana::filebox filebox{*this, true};
      filebox.add_filter("Rom File (*.rom)", "*.rom");
      filebox.add_filter("c8rom File (*.c8rom)", "*.c8rom");
      filebox.add_filter("All Files (*.*)", "*.*");

      if (filebox()) {
        _fileChoosen(filebox.file());
      }
  });
  fileMenu.append_splitter();
  fileMenu.append("Exit", [](nana::menu::item_proxy&) {
      nana::API::exit();
  });

  auto& viewMenu = _menubar.push_back("View");
  viewMenu.append("Debug");

  auto& helpMenu = _menubar.push_back("Help");
  helpMenu.append("About",
                  [this](nana::menu::item_proxy &) {
                    auto msgbox = nana::msgbox{*this, "About c8"}.icon(
                      nana::msgbox::icon_information);
                    msgbox << "Chip8 - interpreter";
                    msgbox.show();
                  });
}

}  // namespace gui
