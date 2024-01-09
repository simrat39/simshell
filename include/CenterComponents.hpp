//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include "components/power/BrightnessSlider.hpp"
#include "components/datetime/DateTimeButton.hpp"
#include "components/workspaces/HyprlandWorkspaces.hpp"

class CenterComponents: public Gtk::Box {
public:
    CenterComponents();
    ~CenterComponents() override;
private:
    DateTimeButton* dtb;
};
