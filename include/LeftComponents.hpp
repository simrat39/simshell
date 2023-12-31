//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include "components/power/BrightnessSlider.hpp"
#include "components/workspaces/HyprlandWorkspaces.hpp"
#include "components/active_window/ActiveWindowLabel.hpp"

class LeftComponents: public Gtk::Box {
public:
    LeftComponents();
    ~LeftComponents() override;
private:
    HyprlandWorkspaces* hpw;
    ActiveWindowLabel* awl;
};
