//
// Created by simrat39 on 12/21/23.
//

#include "MprisButton.hpp"

MprisButton::MprisButton() {
    append(menu_button);
    menu_button.set_icon_name("folder-music-symbolic");
    menu_button.set_popover(popover);
}

MprisButton::~MprisButton() {

}
