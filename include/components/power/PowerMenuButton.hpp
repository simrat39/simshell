//
// Created by simrat39 on 12/23/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include <upower.h>
#include "PowerPopover.hpp"
#include "services/battery/BatteryDevice.hpp"

class PowerMenuButton: public Gtk::Box {
public:
    PowerMenuButton();
    ~PowerMenuButton() override;
private:
    Gtk::MenuButton menu_button;
    PowerPopover power_popover;
    BatteryDevice* main_battery;

    void on_state_change(UpDeviceState state);
};
