//
// Created by simrat39 on 12/25/23.
//

#pragma once

#include <libupower-glib/upower.h>
#include <vector>
#include <memory>
#include "BatteryDevice.hpp"

class BatteryService {
public:
    UpClient* client{};
    std::vector<std::shared_ptr<BatteryDevice>> battery_devices;

    static BatteryService& get_instance();
    BatteryDevice* get_main_battery();
    ~BatteryService();
private:
    BatteryService();
    BatteryService(const BatteryService&);
};
