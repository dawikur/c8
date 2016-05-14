// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_DISPLAY_HPP_
#define INCLUDE_GUI_DISPLAY_HPP_

#include <atomic>
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
                   nana::form const &form);

  void theme(nana::color const fg, nana::color const bg);
  void scale(unsigned const);

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

  static unsigned const Clock = 60;
  static unsigned const Width = 64;
  static unsigned const Height = 32;

  unsigned _width;
  unsigned _height;
  unsigned _scale;

  struct {
    nana::color operator()(Byte const bit) { return bit ? fg : bg; };
    std::atomic<nana::color> fg, bg;
  } _color;

  Byte const *const _memory;
  nana::form const &_form;
  nana::drawing _drawer;
};

}  // namespace gui

#endif  // INCLUDE_GUI_DISPLAY_HPP_
