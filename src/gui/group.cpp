// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/group.hpp"

#include <sstream>

namespace gui {

Group::Group(nana::widget &owner, std::string const &title)
  : nana::panel<true>{owner}
  , _owner{owner}
  , _place{*this}
  , _title{*this, title}
  , _drawer{*this} {
  arrange();

  _drawer.draw([this](nana::paint::graphics &graphics) { draw(graphics); });
}

void Group::arrange() {
  auto const titleSize = _title.measure(1000);
  std::stringstream div;
  div << "vertical margin=12 <weight=" << titleSize.height
      << " <weight=20> <title weight=" << titleSize.width + 1 << "> >";

  _place.div(div.str().c_str());

  _place["title"] << _title;

  _place.collocate();
}

void Group::draw(nana::paint::graphics &graphics) {
  graphics.rectangle(true, _owner.bgcolor());
  graphics.round_rectangle(
    nana::rectangle(20, 20, graphics.width() - 40, graphics.height() - 40),
    5,
    5,
    nana::colors::gray_border,
    true,
    _owner.bgcolor());
}

}  // namespace gui
