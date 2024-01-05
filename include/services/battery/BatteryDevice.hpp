//
// Created by simrat39 on 12/26/23.
//

#pragma once

#include <upower.h>
#include <sigc++/signal.h>

class BatteryDevice {
public:
    UpDevice* up_device;
    sigc::signal<void(UpDeviceState)> signal_state_changed;
    sigc::signal<void(double)> signal_percentage_changed;
    sigc::signal<void(gchar*)> signal_icon_changed;

    explicit BatteryDevice(UpDevice *upDevice);
    ~BatteryDevice();

    UpDeviceState get_state() const;
    double get_percentage() const;
    gchar* get_icon() const;
};