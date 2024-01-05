//
// Created by simrat39 on 12/25/23.
//

#include "services/battery/BatteryService.hpp"
#include <upower.h>
#include <memory>

BatteryService::BatteryService() {
    client = up_client_new();

    auto devices = up_client_get_devices2(client);
    g_ptr_array_foreach(devices, [](gpointer data, gpointer user_data) {
        auto battery_service = reinterpret_cast<BatteryService *>(user_data);

        auto up_device = UP_DEVICE(data);
        battery_service->battery_devices.push_back(std::make_shared<BatteryDevice>(up_device));
    }, this);
}

BatteryService &BatteryService::get_instance() {
    static BatteryService instance;
    return instance;
}

BatteryDevice* BatteryService::get_main_battery() {
    return battery_devices.at(1).get();
}

BatteryService::~BatteryService() = default;
