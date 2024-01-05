//
// Created by simrat39 on 12/24/23.
//

#include "components/workspaces/HyprlandWorkspaceButton.hpp"
#include "services/hyprland/HyprlandService.hpp"

#include <utility>
#include <iostream>
#include <gtkmm/eventcontrollermotion.h>
#include <gtkmm/window.h>

HyprlandWorkspaceButton::HyprlandWorkspaceButton(int id, std::string name): Gtk::Box(), id(id), name(std::move(name)) {
    auto motion_controller = Gtk::EventControllerMotion::create();
    this->add_controller(motion_controller);

    motion_controller->signal_enter().connect([](double x, double y) {
        std::cout << "xx" << std::endl;
    });

    button.add_css_class("workspace_button");
    button.set_label(this->name);
    button.set_can_shrink(true);

    button.signal_clicked().connect(sigc::mem_fun(*this, &HyprlandWorkspaceButton::on_click));

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

HyprlandWorkspaceButton::~HyprlandWorkspaceButton() = default;
