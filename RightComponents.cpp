//
// Created by simrat39 on 12/18/23.
//

#include <gtkmm/menubutton.h>
#include "RightComponents.hpp"
#include "services/backlight/BacklightService.hpp"

RightComponents::RightComponents(): Gtk::Box() {
    this->add_css_class("right_components");

    mpris_button = Gtk::make_managed<MprisButton>();
    this->append(*mpris_button);

    power_button = Gtk::make_managed<PowerMenuButton>();
    this->append(*power_button);

    dtb = Gtk::make_managed<DateTimeButton>();
    append(*dtb);
}

RightComponents::~RightComponents() = default;
