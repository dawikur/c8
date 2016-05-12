// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_DISPLAY_HPP_
#define INCLUDE_GUI_DISPLAY_HPP_

#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <vector>                                                              // fix for nana

#include <nana/gui.hpp>
#include <nana/gui/widgets/form.hpp>

#include "type.hpp"
#include "worker.hpp"

namespace gui {

class Display : public Worker {
 public:
  explicit Display(Byte const *const memory,
                   nana::form const &form,
                   unsigned const width = 64,
                   unsigned const height = 32,
                   unsigned const clock = 60);

 private:
  void do_one() override;
  void draw(nana::paint::graphics &graphics);

  struct Area {
    int x, y;
    unsigned w, h;
    unsigned dx, dy;

    nana::rectangle getBorder() const;
  };
  Area getArea() const;

  unsigned const Width;
  unsigned const Height;

  Byte const *const _memory;
  nana::form const &_form;
  nana::drawing _drawer;
};

}  // namespace gui

#endif  // INCLUDE_GUI_DISPLAY_HPP_
