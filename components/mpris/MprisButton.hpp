//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include "MprisPopover.hpp"

class MprisButton: public Gtk::Box {
public:
    MprisButton();
    ~MprisButton() override;
private:
    Gtk::MenuButton menu_button;
    MprisPopover popover;
};

