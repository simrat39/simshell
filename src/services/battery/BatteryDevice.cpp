//
// Created by simrat39 on 12/26/23.
//

#include <iostream>
#include "services/battery/BatteryDevice.hpp"

void state_cb(gpointer, gpointer, gpointer data) {
    auto device = reinterpret_cast<BatteryDevice*>(data);
    auto state = device->get_state();

    device->signal_state_changed.emit(state);
}

void perc_cb(gpointer, gpointer, gpointer data) {
    auto device = reinterpret_cast<BatteryDevice*>(data);
    auto percentage = device->get_percentage();

    device->signal_percentage_changed.emit(percentage);
}

void icon_cb(gpointer, gpointer, gpointer data) {
    auto device = reinterpret_cast<BatteryDevice*>(data);
    auto icon = device->get_icon();

    device->signal_icon_changed.emit(icon);
}

BatteryDevice::BatteryDevice(UpDevice *upDevice) : up_device(upDevice) {
    g_signal_connect(up_device, "notify::state", G_CALLBACK(state_cb), this);
    g_signal_connect(up_device, "notify::percentage", G_CALLBACK(perc_cb), this);
    g_signal_connect(up_device, "notify::icon-name", G_CALLBACK(icon_cb), this);
}

UpDeviceState BatteryDevice::get_state() const {
    UpDeviceState state;
    g_object_get(up_device, "state", &state, nullptr);

    return state;
}

double BatteryDevice::get_percentage() const {
    double percentage;
    g_object_get(up_device, "percentage", &percentage, nullptr);

    return percentage;
}

gchar *BatteryDevice::get_icon() const {
    gchar* icon;
    g_object_get(up_device, "icon-name", &icon, nullptr);

    return icon;
}

BatteryDevice::~BatteryDevice() = default;
