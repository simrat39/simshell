//
// Created by simrat39 on 12/21/23.
//

#include "components/mpris/MprisButton.hpp"

MprisButton::MprisButton() {
    menu_button.add_css_class("mpris_button");
    append(menu_button);
    menu_button.set_icon_name("folder-music-symbolic");
    menu_button.set_popover(popover);
}

MprisButton::~MprisButton() {

}
