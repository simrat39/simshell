//
// Created by simrat39 on 12/18/23.
//

#include "../include/RootBar.hpp"
#include "../include/CenterComponents.hpp"
#include "../include/RightComponents.hpp"

RootBar::RootBar() {
  left = Gtk::make_managed<LeftComponents>();
  center = Gtk::make_managed<CenterComponents>();
  right = Gtk::make_managed<RightComponents>();

  c_box.set_start_widget(*left);
  c_box.set_center_widget(*center);
  c_box.set_end_widget(*right);

  this->set_child(c_box);
}

RootBar::~RootBar() = default;
