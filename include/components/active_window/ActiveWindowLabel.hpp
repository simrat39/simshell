//
// Created by simrat39 on 12/23/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include "../../services/hyprland/HyprlandService.hpp"

class ActiveWindowLabel: public Gtk::Box {
public:
    ActiveWindowLabel();
    ~ActiveWindowLabel() override;

    void update(HyprlandService::HyprlandEvent event, std::string data);
private:
    Gtk::Label label;
};
