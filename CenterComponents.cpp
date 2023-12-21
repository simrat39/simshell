//
// Created by simrat39 on 12/18/23.
//

#include "CenterComponents.hpp"
#include "services/backlight/BacklightService.hpp"

CenterComponents::CenterComponents(): Gtk::Box() {
    dtb = new DateTimeButton();

    append(*dtb);
}

CenterComponents::~CenterComponents() {
    delete dtb;
};
