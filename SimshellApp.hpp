//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/application.h>
#include "services/hyprland/HyprlandService.hpp"

class SimshellApp: public Gtk::Application {
public:
    SimshellApp();
    static Glib::RefPtr<SimshellApp> create();
protected:
    void on_activate() override;

};

