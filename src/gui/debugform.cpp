// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/debugform.hpp"


namespace gui {

Debugform::Debugform()
  : _place{*this}, _opcodes{*this}, _registers{*this, "Registers:"} {
  caption("c8 - debug");

  arrange();
}

void Debugform::run() {
  show();
}

void Debugform::arrange() {
  _place.div("<margin=10 gap=10 horizontal debug>");

  _opcodes.append_header("Addr");
  _opcodes.append_header("Hex");
  _opcodes.append_header("Asm");

  _place["debug"] << _opcodes << _registers;

  _place.collocate();
}

}  // namespace gui
