//
// Created by simrat39 on 12/18/23.
//

#include <gtkmm/menubutton.h>
#include "RightComponents.hpp"
#include "services/backlight/BacklightService.hpp"

RightComponents::RightComponents(): Gtk::Box() {
    mpris_button = Gtk::make_managed<MprisButton>();
    this->append(*mpris_button);

    power_button = Gtk::make_managed<PowerMenuButton>();
    this->append(*power_button);
}

RightComponents::~RightComponents() = default;
