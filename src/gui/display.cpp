// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/display.hpp"

namespace gui {

Display::Display(Byte *memory,
                 nana::form &form,
                 unsigned const Width,
                 unsigned const Height)
  : Width{Width}
  , Height{Height}
  , _memory{memory}
  , _form{form}
  , _drawer{_form} {
  _drawer.draw([this](nana::paint::graphics &graphics) { draw(graphics); });
}

void Display::draw(nana::paint::graphics &graphics) {
  auto const area = getArea();

  graphics.rectangle(area.getBorder(), false, nana::colors::black);

  for (int x = 0; x < Width; ++x) {
    for (int y = 0; y < Height; ++y) {
      auto const color = nana::colors::black;

      graphics.rectangle(
        nana::rectangle{static_cast<int>(area.x + x * area.dx),
                        static_cast<int>(area.y + y * area.dy),
                        area.dx,
                        area.dy},
        true,
        color);
    }
  }
}

Display::Area Display::getArea() {
  auto constexpr topOffset = 28;

  auto const fullSize = _form.size();

  unsigned const width = (fullSize.width - 2)  / Width  * Width;
  unsigned const height = (fullSize.height - (topOffset + 2)) / Height * Height;

  int const dx = (fullSize.width - width) / 2;
  int const dy = (fullSize.height - topOffset - height) / 2;

  return {
    dx + 1, dy + topOffset + 1, width, height, width / Width, height / Height};
}

nana::rectangle Display::Area::getBorder() const {
  return {x - 1, y - 1, w + 2, h + 2};
}

}  // namespace gui
