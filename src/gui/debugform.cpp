// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "gui/debugform.hpp"


namespace gui {

Debugform::Debugform()
  : _place{*this}, _opcodes{*this}, _registers{*this, "Registers:"}, _buttons{*this} {
  caption("c8 - debug");

  arrange();
}

void Debugform::run() {
  show();
}

void Debugform::arrange() {
  _place.div(
    "<margin=10 gap=10 vertical <horizontal debug> <weight=50 horizontal <> "
    "<margin=10 gap=10 weight=500 horizontal control> > >");

  _opcodes.append_header("Addr");
  _opcodes.append_header("Hex");
  _opcodes.append_header("Asm");

  _place["debug"] << _opcodes << _registers;


  _buttons._continue.caption("&Continue");
  _buttons._pause.caption("&Pause");
  _buttons._step.caption("&Step");
  _buttons._stop.caption("St&op");
  _place["control"] << _buttons._continue << _buttons._pause << _buttons._step
                    << _buttons._stop;

  _place.collocate();
}

}  // namespace gui
