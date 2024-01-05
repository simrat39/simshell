//
// Created by simrat39 on 12/18/23.
//

#include "RightComponents.hpp"
#include "services/battery/BatteryService.hpp"
#include <gtkmm/menubutton.h>

RightComponents::RightComponents() : Gtk::Box() {
  this->add_css_class("right_components");

  mpris_button = Gtk::make_managed<MprisButton>();
  this->append(*mpris_button);

  power_button = Gtk::make_managed<PowerMenuButton>();
  this->append(*power_button);

  BatteryService::get_instance();
}

RightComponents::~RightComponents() = default;
