//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/widget.h>
#include <gtkmm/scale.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include "../services/backlight/BacklightService.hpp"

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

    bool set_by_slider = false;

    inline static const char *SYSTEMD_DBUS_NAME = "org.freedesktop.login1";
    inline static const char *SYSTEMD_DBUS_PATH = "/org/freedesktop/login1/session/auto";
    inline static const char *SYSTEMD_DBUS_INTERFACE = "org.freedesktop.login1.Session";
};
