// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/display.hpp"
#include <iostream>

namespace gui {

Display::Display(Byte const *const memory,
                 nana::form const &form,
                 unsigned const width,
                 unsigned const height,
                 unsigned const clock)
  : Worker{clock}
  , Width{width}
  , Height{height}
  , _color{}
  , _memory{memory}
  , _form{form}
  , _drawer{_form} {
  _drawer.draw([this](nana::paint::graphics &graphics) { draw(graphics); });
  theme(nana::colors::black, nana::colors::white);
  start();
}

void Display::do_one() {
  _drawer.update();
}

void Display::draw(nana::paint::graphics &graphics) {
  auto const area = getArea();

  graphics.rectangle(area.getBorder(), false, nana::colors::black);

  for (int y = 0; y < Height; ++y) {
    for (int x = 0; x < Width; ++x) {
      auto const pos = x + (y * Width);
      auto const bit = (_memory[pos / 8] >> (7 - pos % 8)) & 0x01;

      graphics.rectangle(
        nana::rectangle{static_cast<int>(area.x + x * area.dx),
                        static_cast<int>(area.y + y * area.dy),
                        area.dx,
                        area.dy},
        true,
        _color(bit));
    }
  }
}

void Display::theme(nana::color const fg, nana::color const bg) {
  _color.fg = fg;
  _color.bg = bg;
  do_one();
}

Display::Area Display::getArea() const {
  auto constexpr topOffset = 28;

  auto const fullSize = _form.size();

  unsigned const width = (fullSize.width - 2) / Width * Width;
  unsigned const height =
    (fullSize.height - (topOffset + 2)) / Height * Height;

  int const dx = (fullSize.width - width) / 2;
  int const dy = (fullSize.height - topOffset - height) / 2;

  return {
    dx + 1, dy + topOffset + 1, width, height, width / Width, height / Height};
}

nana::rectangle Display::Area::getBorder() const {
  return {x - 1, y - 1, w + 2, h + 2};
}

}  // namespace gui
