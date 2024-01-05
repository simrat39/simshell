//
// Created by simrat39 on 12/20/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/calendar.h>
#include <gtkmm/label.h>

class DateTimeButton: public Gtk::Box {
public:
    DateTimeButton();
    ~DateTimeButton() override;
private:
    Gtk::Label label;
    Gtk::MenuButton menu_button;
    Gtk::Popover popover;
    Gtk::Calendar calendar;

    Glib::DateTime time_now;

    bool time_update();
};
