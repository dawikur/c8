// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_DEBUGFORM_HPP_
#define INCLUDE_GUI_DEBUGFORM_HPP_

#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <vector>                                                              // fix dor nana

#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/place.hpp>

#include "gui/group.hpp"

namespace gui {

class Debugform : public nana::form {
 public:
  Debugform();

  void run();

 private:
  void arrange();

  nana::place _place;

  nana::listbox _opcodes;
  Group _registers;

  struct Buttons {
    Buttons(nana::widget &owner)
      : _continue{owner}, _pause{owner}, _step{owner}, _stop{owner} {}

    nana::button _continue;
    nana::button _pause;
    nana::button _step;
    nana::button _stop;
  } _buttons;
};

}  // namespace gui

#endif  // INCLUDE_GUI_DEBUGFORM_HPP_

