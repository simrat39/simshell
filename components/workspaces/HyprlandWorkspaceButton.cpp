//
// Created by simrat39 on 12/24/23.
//

#include "HyprlandWorkspaceButton.hpp"
#include "../../services/hyprland/HyprlandService.hpp"

#include <utility>
#include <iostream>
#include <gtkmm/eventcontrollermotion.h>

HyprlandWorkspaceButton::HyprlandWorkspaceButton(int id, std::string name): Gtk::Box(), id(id), name(std::move(name)) {
    button.add_css_class("workspace_button");
    button.set_label(this->name);
    button.set_can_shrink(true);

    button.signal_clicked().connect(sigc::mem_fun(*this, &HyprlandWorkspaceButton::on_click));
    button.signal_state_flags_changed().connect(sigc::mem_fun(*this, &HyprlandWorkspaceButton::on_state_change));

    append(button);
}

void HyprlandWorkspaceButton::set_current() {
    if (!current) {
        button.add_css_class("workspace_button_selected");
        current = true;
    };
}

void HyprlandWorkspaceButton::unset_current() {
    if (current) {
        button.remove_css_class("workspace_button_selected");
        current = false;
    }
}

void HyprlandWorkspaceButton::on_click() {
    std::string msg = "dispatch workspace " + name;
    HyprlandService::get_instance().hyperctl_request(msg.c_str());
}

void HyprlandWorkspaceButton::on_state_change(Gtk::StateFlags oldState) {
    if ((get_state_flags() & Gtk::StateFlags::PRELIGHT) == Gtk::StateFlags::PRELIGHT) {
//        std::cout << name + " is being hovered" << std::endl;
    } else {
//        std::cout << (int)get_state_flags() << std::endl;
    }
}

HyprlandWorkspaceButton::~HyprlandWorkspaceButton() = default;
