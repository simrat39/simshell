//
// Created by simrat39 on 12/18/23.
//

#include "components/BrightnessSlider.hpp"
#include <giomm/themedicon.h>
#include "services/backlight/BacklightService.hpp"
#include <glibmm/main.h>

BrightnessSlider::BrightnessSlider(GUdevDevice *device) : Gtk::Box(), device(device) {
    this->set_margin_start(10);
    this->set_margin_end(10);

    img.set_margin_end(5);

    this->append(img);
    this->append(scale);

    scale.set_range(0, 100);
    scale.set_hexpand(true);

    auto max_brightness = g_udev_device_get_sysfs_attr_as_int(device, "max_brightness");
    auto cur_brightness = g_udev_device_get_sysfs_attr_as_int(device, "brightness");

    auto scaled = ((double) cur_brightness) / max_brightness;
    scale.set_value(scaled * 100);

    img.set(Gio::ThemedIcon::create("display-brightness-symbolic"));

    scale.signal_value_changed().connect(
            sigc::mem_fun(*this, &BrightnessSlider::on_scale_value_changed));
}

void BrightnessSlider::on_map() {
    Widget::on_map();

    BacklightService::get_instance().add_listener("slider", [this](GUdevClient *client, const gchar *action,
                                                                       GUdevDevice *udev_device,
                                                                       BacklightService *user_data) {
        if (!set_by_slider) {
            auto myName = g_udev_device_get_name(this->device);
            auto inName = g_udev_device_get_name(udev_device);

            if (strcmp(myName, inName) == 0) {
                auto max_brightness = g_udev_device_get_sysfs_attr_as_int(udev_device, "max_brightness");
                auto cur_brightness = g_udev_device_get_sysfs_attr_as_int(udev_device, "brightness");

                auto scaled = ((double) cur_brightness) / max_brightness;
                scale.set_value(scaled * 100);
            }
        }
        set_by_slider = false;
    });
}

void BrightnessSlider::on_unmap() {
    Widget::on_unmap();

    BacklightService::get_instance().remove_listener("slider");
}


void BrightnessSlider::on_scale_value_changed() {
    auto conn = Gio::DBus::Connection::get_sync(Gio::DBus::BusType::SYSTEM);
    auto proxy = Gio::DBus::Proxy::create_sync(
            conn,
            SYSTEMD_DBUS_NAME,
            SYSTEMD_DBUS_PATH,
            SYSTEMD_DBUS_INTERFACE,
            nullptr, {});

    auto v = Glib::Variant<std::tuple<Glib::ustring, Glib::ustring, guint>>::create(std::make_tuple("backlight",
                                                                                                    g_udev_device_get_name(
                                                                                                            this->device),
                                                                                                    255 *
                                                                                                    scale.get_value() /
                                                                                                    100));
    proxy->call_sync("SetBrightness", v);
    set_by_slider = true;
}

BrightnessSlider::~BrightnessSlider() = default;
