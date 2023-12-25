//
// Created by simrat39 on 12/24/23.
//

#include "HyprlandWorkspaceButton.hpp"

#include <utility>

HyprlandWorkspaceButton::HyprlandWorkspaceButton(int id, std::string name): Gtk::Box(), id(id), name(std::move(name)) {
    button.add_css_class("workspace_button");
    button.set_label(this->name);
    button.set_can_shrink(true);

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

HyprlandWorkspaceButton::~HyprlandWorkspaceButton() = default;
