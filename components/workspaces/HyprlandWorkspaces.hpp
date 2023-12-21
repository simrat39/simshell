//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include <gtkmm/box.h>
#include <set>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include "../../services/hyprland/HyprlandService.hpp"

class HyprlandWorkspaces: public Gtk::Box {
public:
    HyprlandWorkspaces();
    ~HyprlandWorkspaces() override;
private:
    void hyperland_data_cb(HyprlandService::HyprlandEvent event, const std::string& data);

    std::set<std::string> workspaces;
    std::set<std::pair<std::string, Gtk::Button>> ws_widgets;
    Gtk::Label label;
};