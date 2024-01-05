//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <string>
#include <vector>
#include <gtkmm-4.0/gtkmm.h>
#include <gudev/gudev.h>

class BacklightService {
public:
    static BacklightService get_instance();

    GList *get_devices();

    static void udev_callback(GUdevClient *client, const gchar *action, GUdevDevice *device, gpointer user_data);

    void add_listener(std::string_view id, std::function<void(GUdevClient *client, const gchar *action,
                                                              GUdevDevice *device,
                                                              BacklightService *user_data)> callback) const;

    void remove_listener(std::string_view id) const;

private:
    BacklightService();

    GUdevClient *client;

    std::unordered_map<std::string_view, std::function<void(GUdevClient *client, const gchar *action,
                                                            GUdevDevice *device,
                                                            BacklightService *user_data)>>* listeners;
};

