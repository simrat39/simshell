//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/widget.h>
#include <gtkmm/scale.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include "../services/backlight/BrightnessService.hpp"

class BrightnessSlider: public Gtk::Box {
public:
    explicit BrightnessSlider(GUdevDevice* device);
    ~BrightnessSlider() override;

    void on_scale_value_changed();
protected:
    void on_map() override;
    void on_unmap() override;
private:
    Gtk::Image img;
    Gtk::Scale scale;
    GUdevDevice* device;

    sigc::connection on_scale_value_changed_connection;
    bool set_by_slider = false;
};
