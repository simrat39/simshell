//
// Created by simrat39 on 12/23/23.
//

#include "PowerMenuButton.hpp"

PowerMenuButton::PowerMenuButton() {
    menu_button.set_icon_name("display-brightness-symbolic");
    menu_button.set_popover(power_popover);

    append(menu_button);
}

PowerMenuButton::~PowerMenuButton() = default;
