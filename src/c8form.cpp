// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "c8form.hpp"

#include <string>

#include <nana/gui/filebox.hpp>
#include <nana/gui/wvl.hpp>

C8form::C8form()
  : nana::form{}, fileChoosenCallback{[](std::string const &) {}}, menubar{*this} {
  caption("c8");

  bgcolor(nana::colors::white);
  menubar.bgcolor(nana::colors::white);

  createMenubar();
}

void C8form::exec() {
  show();
  nana::exec();
}

void C8form::fileChoosen(FileChoosen const &callback) {
  fileChoosenCallback = callback;
}

void C8form::createMenubar() {
  auto& fileMenu = menubar.push_back("File");
  fileMenu.append("Open", [this](nana::menu::item_proxy&) {
      nana::filebox filebox{*this, true};
      filebox.add_filter("Rom File", "*.rom");
      filebox.add_filter("c8rom File", "*.c8rom");
      filebox.add_filter("All Files", "*.*");

      if (filebox()) {
        fileChoosenCallback(filebox.file());
      }
  });
  fileMenu.append_splitter();
  fileMenu.append("Exit", [](nana::menu::item_proxy&) {
      nana::API::exit();
  });

  auto& viewMenu = menubar.push_back("View");

  auto& helpMenu = menubar.push_back("Help");
  helpMenu.append("About",
                  [this](nana::menu::item_proxy &) {
                    auto msgbox = nana::msgbox{*this, "About c8"}.icon(
                      nana::msgbox::icon_information);
                    msgbox << "Chip8 - emulator";
                    msgbox.show();
                  });
}

