//
// Created by simrat39 on 12/18/23.
//

#include "../include/CenterComponents.hpp"

CenterComponents::CenterComponents(): Gtk::Box() {
    this->add_css_class("center_components");

    dtb = Gtk::make_managed<DateTimeButton>();
    append(*dtb);
}

CenterComponents::~CenterComponents() = default;
