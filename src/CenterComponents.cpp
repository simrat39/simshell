//
// Created by simrat39 on 12/18/23.
//

#include "../include/CenterComponents.hpp"
#include "services/backlight/BacklightService.hpp"

CenterComponents::CenterComponents(): Gtk::Box() {
    dtb = Gtk::make_managed<DateTimeButton>();
    append(*dtb);
}

CenterComponents::~CenterComponents() = default;
