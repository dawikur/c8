// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/display.hpp"
#include "hqx/hqx.hpp"

namespace gui {

Display::Display(Byte const *const memory,
                 nana::form const &form)
  : Worker{Clock}
  , _width{Width}
  , _height{Height}
  , _scale{}
  , _isUpdateNeeded{true}
  , _color()
  , _hqx{memory, Width, Height}
  , _form{form}
  , _drawer{_form} {
  _drawer.draw([this](nana::paint::graphics &graphics) { draw(graphics); });
  theme(nana::colors::black, nana::colors::white);
  scale(1);
  start();
}

void Display::do_one() {
  if (_isUpdateNeeded) {
    _hqx.rescale(_scale);
    _isUpdateNeeded = false;
  }
  _drawer.update();
}

void Display::draw(nana::paint::graphics &graphics) {
  auto const area = getArea();
  auto const& data = _hqx();

  graphics.rectangle(area.getBorder(), false, nana::colors::black);

  for (unsigned y = 0; y < _height; ++y) {
    for (unsigned x = 0; x < _width; ++x) {
      auto const pos = x + (y * _width);
      auto const bit = data[pos];

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
}

void Display::scale(unsigned const scale) {
  _scale = scale;
  _width = Width * scale;
  _height = Height * scale;
}

UpdateDisplay Display::updateCallback() {
  return [this]() { _isUpdateNeeded = true; };
}

Display::Area Display::getArea() const {
  auto constexpr topOffset = 28;

  auto const fullSize = _form.size();

  unsigned const width = ((fullSize.width - 2) / _width) * _width;             // round down
  unsigned const height =
    (fullSize.height - (topOffset + 2)) / _height * _height;                   // round down

  int const dx = (fullSize.width - width) / 2;
  int const dy = (fullSize.height - topOffset - height) / 2;

  return {dx + 1,
          dy + topOffset + 1,
          width,
          height,
          width / _width,
          height / _height};
}

nana::rectangle Display::Area::getBorder() const {
  return {x - 1, y - 1, w + 2, h + 2};
}

}  // namespace gui
