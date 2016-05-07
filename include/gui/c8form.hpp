// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_C8FORM_HPP_
#define INCLUDE_GUI_C8FORM_HPP_

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

#include "display.hpp"

namespace gui {

class C8form : public nana::form {
 public:
  using FileChoosen = std::function<void (std::string const&)>;

  C8form();

  void exec();

  void fileChoosen(FileChoosen const &callback);

 private:
  void createMenubar();

  nana::drawing drawer;
  nana::menubar menubar;
  FileChoosen fileChoosenCallback;
};

}  // namespace gui

#endif  // INCLUDE_GUI_C8FORM_HPP_
