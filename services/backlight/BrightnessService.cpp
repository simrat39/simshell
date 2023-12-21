//
// Created by simrat39 on 12/18/23.
//

#include "BrightnessService.hpp"

#include <gudev/gudev.h>
#include <iostream>
#include <utility>

BrightnessService::BrightnessService() {
    // start listening here
    const gchar* const subsystems[] = {"backlight", nullptr};

    this->client = g_udev_client_new(subsystems);
    this->listeners = new std::unordered_map<std::string_view, std::function<void(GUdevClient *client, const gchar *action,
                                                                                  GUdevDevice *device,
                                                                                  BrightnessService *user_data)>>{};

    g_signal_connect(client, "uevent", G_CALLBACK (&BrightnessService::udev_callback), this);
}

BrightnessService BrightnessService::get_instance() {
    static auto instance = BrightnessService{};
    return instance;
}

GList* BrightnessService::get_devices() {
    auto devices = g_udev_client_query_by_subsystem(client, "backlight");
    return devices;
}

void BrightnessService::udev_callback(GUdevClient *client, const gchar *action, GUdevDevice *device, gpointer user_data) {
    auto* cur_instance = static_cast<BrightnessService*>(user_data);

    for (const auto& k: *cur_instance->listeners) {
        k.second(client, action, device, cur_instance);
    }
}

void BrightnessService::add_listener(std::string_view id,
                                     std::function<void(GUdevClient *, const gchar *, GUdevDevice *,
                                                        BrightnessService *)> callback) const {
    (*listeners)[id] = std::move(callback);
}

void BrightnessService::remove_listener(std::string_view id) const {
    auto iter = listeners->find(id);

    if (iter != listeners->end()) {
        listeners->erase(iter);
    }
}

