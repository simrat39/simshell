//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include "components/BrightnessSlider.hpp"

class RightComponents: public Gtk::Box {
public:
    RightComponents();
    ~RightComponents() override;
protected:
    void on_map() override;
    void on_unmap() override;
private:
    Gtk::MenuButton mb;
    Gtk::Popover popover;

    std::vector<BrightnessSlider*> brightness_sliders;
};
