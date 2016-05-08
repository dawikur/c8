// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_DISPLAY_HPP_
#define INCLUDE_GUI_DISPLAY_HPP_

#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <vector>                                                              // fix for nana

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>

#include "type.hpp"

namespace gui {

class Display {
 public:
  explicit Display(Byte const *const memory,
                   nana::form &form,
                   unsigned const Width = 64,
                   unsigned const Height = 32);

  void update();

 private:
  void draw(nana::paint::graphics &graphics);

  struct Area {
    int x, y;
    unsigned w, h;
    unsigned dx, dy;

    nana::rectangle getBorder() const;
  };
  Area getArea();

  unsigned const Width;
  unsigned const Height;

  Byte const *const _memory;
  nana::form &_form;
  nana::drawing _drawer;
};

}  // namespace gui

#endif  // INCLUDE_GUI_DISPLAY_HPP_
