// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_C8FORM_HPP_
#define INCLUDE_C8FORM_HPP_

#include <stdexcept>
#include <memory>
#include <vector>

#include <nana/basic_types.hpp>
#include <nana/gui/filebox.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/wvl.hpp>

class c8form : public nana::form {
 public:
  c8form() : nana::form{}, menubar{*this} {
    caption("c8");

    bgcolor(nana::colors::white);
    menubar.bgcolor(nana::colors::white);

    createMenubar();
  }

  void exec() {
    show();
    nana::exec();
  }

 private:
  void createMenubar() {
    auto& fileMenu = menubar.push_back("&File");
    fileMenu.append("&Open", [this](nana::menu::item_proxy&) {
        nana::filebox filebox{*this, true};
        filebox.add_filter("Rom File", "*.rom");
        filebox.add_filter("c8rom File", "*.c8rom");
        filebox.add_filter("All Files", "*.*");

        filebox();
    });
    fileMenu.append_splitter();
    fileMenu.append("&Exit", [](nana::menu::item_proxy&) {
        nana::API::exit();
    });

    menubar.push_back("&View");
    auto& helpMenu = menubar.push_back("&Help");
    helpMenu.append("&About",
                    [this](nana::menu::item_proxy &) {
                      auto msgbox = nana::msgbox{*this, "About c8"}.icon(
                        nana::msgbox::icon_information);
                      msgbox << "Chip8 - emulator";
                      msgbox.show();
                    });
  }

  nana::menubar menubar;
};

#endif  // INCLUDE_C8FORM_HPP_

