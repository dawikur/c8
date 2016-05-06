// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef INCLUDE_C8FORM_HPP_
#define INCLUDE_C8FORM_HPP_

#include <stdexcept>
#include <memory>
#include <vector>

#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/menubar.hpp>

class c8form : public nana::form {
 public:
  c8form();

  void exec();

 private:
  void createMenubar();

  nana::menubar menubar;
};

#endif  // INCLUDE_C8FORM_HPP_

