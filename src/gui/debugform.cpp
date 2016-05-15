// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/debugform.hpp"

#include <nana/gui/place.hpp>

namespace gui {

Debugform::Debugform() {
  caption("c8 - debug");

  arrange();
}

void Debugform::run() {
  show();
}

void Debugform::arrange() {
  nana::place place{*this};
}

}  // namespace gui
