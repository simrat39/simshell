//
// Created by simrat39 on 12/23/23.
//

#pragma once

#include <gtkmm/popover.h>
#include <gtkmm/box.h>
#include "../BrightnessSlider.hpp"

class PowerPopover: public Gtk::Popover {
public:
    PowerPopover();
    ~PowerPopover() override;
protected:
    void on_map() override;
    void on_unmap() override;
private:
    Gtk::Box content;
    std::vector<BrightnessSlider*> brightness_sliders;
};
