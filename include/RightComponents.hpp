//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include "components/mpris/MprisButton.hpp"
#include "components/power/PowerMenuButton.hpp"
#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>

class RightComponents : public Gtk::Box {
public:
  RightComponents();
  ~RightComponents() override;

private:
  PowerMenuButton *power_button;
  MprisButton *mpris_button;
};
