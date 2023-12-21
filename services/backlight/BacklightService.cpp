//
// Created by simrat39 on 12/18/23.
//

#include "BacklightService.hpp"

#include <gudev/gudev.h>
#include <iostream>
#include <utility>

BacklightService::BacklightService() {
    // start listening here
    const gchar* const subsystems[] = {"backlight", nullptr};

    this->client = g_udev_client_new(subsystems);
    this->listeners = new std::unordered_map<std::string_view, std::function<void(GUdevClient *client, const gchar *action,
                                                                                  GUdevDevice *device,
                                                                                  BacklightService *user_data)>>{};

    g_signal_connect(client, "uevent", G_CALLBACK (&BacklightService::udev_callback), this);
}

BacklightService BacklightService::get_instance() {
    static auto instance = BacklightService{};
    return instance;
}

GList* BacklightService::get_devices() {
    auto devices = g_udev_client_query_by_subsystem(client, "backlight");
    return devices;
}

void BacklightService::udev_callback(GUdevClient *client, const gchar *action, GUdevDevice *device, gpointer user_data) {
    auto* cur_instance = static_cast<BacklightService*>(user_data);

    for (const auto& k: *cur_instance->listeners) {
        k.second(client, action, device, cur_instance);
    }
}

void BacklightService::add_listener(std::string_view id,
                                    std::function<void(GUdevClient *, const gchar *, GUdevDevice *,
                                                       BacklightService *)> callback) const {
    (*listeners)[id] = std::move(callback);
}

void BacklightService::remove_listener(std::string_view id) const {
    auto iter = listeners->find(id);

    if (iter != listeners->end()) {
        listeners->erase(iter);
    }
}

