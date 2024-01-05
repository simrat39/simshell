//
// Created by simrat39 on 12/23/23.
//

#include <iostream>
#include "components/power/PowerMenuButton.hpp"
#include "services/battery/BatteryService.hpp"

std::string get_icon(UpDeviceState state, double percentage) {
    switch (state) {
        case UP_DEVICE_STATE_UNKNOWN:
            return "battery-missing";
        case UP_DEVICE_STATE_PENDING_CHARGE:
        case UP_DEVICE_STATE_CHARGING:
            return "battery-empty-charging";
        case UP_DEVICE_STATE_PENDING_DISCHARGE:
        case UP_DEVICE_STATE_DISCHARGING:
            if (percentage < 33) {
                return "battery-low";
            } else if (percentage < 66) {
                return "battery-good";
            } else if (percentage <= 100) {
                return "battery-full";
            }
            break;
        case UP_DEVICE_STATE_EMPTY:
            return "battery-empty";
        case UP_DEVICE_STATE_FULLY_CHARGED:
            return "battery-full-charging";
        case UP_DEVICE_STATE_LAST:
            return "battery-caution";
    }
}

PowerMenuButton::PowerMenuButton() {
    main_battery = BatteryService::get_instance().get_main_battery();

    main_battery->signal_state_changed.connect(sigc::mem_fun(*this, &PowerMenuButton::on_state_change));

    main_battery->signal_percentage_changed.connect([&](double perc) {
        auto icon = get_icon(main_battery->get_state(), main_battery->get_percentage());
        menu_button.set_icon_name(icon);
    });

    auto icon = get_icon(main_battery->get_state(), main_battery->get_percentage());
    menu_button.set_icon_name(icon);
    menu_button.set_popover(power_popover);

    append(menu_button);
}

void PowerMenuButton::on_state_change(UpDeviceState state) {
    auto icon = get_icon(state, main_battery->get_percentage());

    menu_button.set_icon_name(icon);
}

PowerMenuButton::~PowerMenuButton() = default;
