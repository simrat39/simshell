//
// Created by simrat39 on 12/20/23.
//

#include "DateTimeButton.hpp"
#include <glibmm.h>

DateTimeButton::DateTimeButton(): Gtk::Box() {
    append(menu_button);

    menu_button.set_child(label);
    time_now = Glib::DateTime::create_now_local();
    label.set_label(time_now.format("%b %d %I:%M %p"));

    menu_button.set_popover(popover);
    popover.set_child(calendar);

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &DateTimeButton::time_update), 1000);
}

bool DateTimeButton::time_update() {
    time_now = Glib::DateTime::create_now_local();
    label.set_label(time_now.format("%b %d %I:%M %p"));
    return true;
}

DateTimeButton::~DateTimeButton() = default;
