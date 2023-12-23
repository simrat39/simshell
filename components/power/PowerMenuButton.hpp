//
// Created by simrat39 on 12/23/23.
//

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include "PowerPopover.hpp"

class PowerMenuButton: public Gtk::Box {
public:
    PowerMenuButton();
    ~PowerMenuButton() override;
private:
    Gtk::MenuButton menu_button;
    PowerPopover power_popover;
};