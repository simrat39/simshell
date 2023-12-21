//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/menubutton.h>
#include "components/BrightnessSlider.hpp"

class RightComponentsHolder: public Gtk::Box {
public:
    RightComponentsHolder();
    ~RightComponentsHolder() override;
protected:
    void on_show() override;
    void on_unmap() override;
private:
    Gtk::MenuButton mb;
    std::vector<BrightnessSlider*> brightness_sliders;
};
