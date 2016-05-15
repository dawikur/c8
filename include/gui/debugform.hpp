// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_GUI_DEBUGFORM_HPP_
#define INCLUDE_GUI_DEBUGFORM_HPP_

#include <memory>                                                              // fix for nana
#include <stdexcept>                                                           // fix for nana
#include <vector>                                                              // fix dor nana

#include <nana/gui/widgets/form.hpp>

namespace gui {

class Debugform : public nana::form {
 public:
  Debugform();

  void run();

 private:
  void arrange();
};

}  // namespace gui

#endif  // INCLUDE_GUI_DEBUGFORM_HPP_

