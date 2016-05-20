// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_GROUP_HPP_
#define INCLUDE_GUI_GROUP_HPP_

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/panel.hpp>

#include <string>

namespace gui {

class Group : public nana::panel<true> {
 public:
  Group(nana::widget& owner, std::string const &title);

 private:
  void arrange();
  void draw(nana::paint::graphics &graphics);

  nana::widget &_owner;
  nana::place _place;
  nana::label _title;
  nana::drawing _drawer;
};

}  // namespace gui

#endif  // INCLUDE_GUI_GROUP_HPP_
