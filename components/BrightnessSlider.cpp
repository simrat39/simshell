//
// Created by simrat39 on 12/18/23.
//

#include <iostream>
#include "BrightnessSlider.hpp"
#include <giomm/themedicon.h>
#include <glibmm/main.h>

BrightnessSlider::BrightnessSlider(GUdevDevice* device) : Gtk::Box(), device(device) {
    this->set_margin_start(10);
    this->set_margin_end(10);

    img.set_margin_end(5);

    this->append(img);
    this->append(scale);

    scale.set_range(0, 100);
    scale.set_hexpand(true);
    on_scale_value_changed_connection = scale.signal_value_changed().connect(sigc::mem_fun(*this, &BrightnessSlider::on_scale_value_changed));

    img.set(Gio::ThemedIcon::create("display-brightness-symbolic"));
}

void BrightnessSlider::on_map() {
    Widget::on_map();

    BrightnessService::get_instance().add_listener("bbbb", [this](GUdevClient *client, const gchar *action,
                                                              GUdevDevice *udev_device,
                                                              BrightnessService *user_data){
        if (!set_by_slider) {
            auto myName = g_udev_device_get_name(this->device);
            auto inName = g_udev_device_get_name(udev_device);

            if (strcmp(myName,inName) == 0) {
                auto max_brightness = g_udev_device_get_sysfs_attr_as_int(udev_device, "max_brightness");
                auto cur_brightness = g_udev_device_get_sysfs_attr_as_int(udev_device, "brightness");

                auto scaled = ((double)cur_brightness) / max_brightness;
//                on_scale_value_changed_connection.disconnect();
                scale.set_value(scaled * 100);
//                on_scale_value_changed_connection = scale.signal_value_changed().connect(sigc::mem_fun(*this, &BrightnessSlider::on_scale_value_changed));
            }
        }
        set_by_slider = false;
    });
}

void BrightnessSlider::on_unmap() {
    Widget::on_unmap();
}

const char* SYSTEMD_DBUS_NAME = "org.freedesktop.login1";
const char* SYSTEMD_DBUS_PATH = "/org/freedesktop/login1/session/auto";
const char* SYSTEMD_DBUS_INTERFACE = "org.freedesktop.login1.Session";

void BrightnessSlider::on_scale_value_changed() {
        auto conn = Gio::DBus::Connection::get_sync(Gio::DBus::BusType::SYSTEM);
        auto proxy = Gio::DBus::Proxy::create_sync(
                conn,
                SYSTEMD_DBUS_NAME,
                SYSTEMD_DBUS_PATH,
                SYSTEMD_DBUS_INTERFACE,
                nullptr, {});

        auto v = Glib::Variant<std::tuple<Glib::ustring, Glib::ustring, guint>>::create(std::make_tuple("backlight",
                                                                                                        "amdgpu_bl1", 255 * scale.get_value() / 100));
        proxy->call_sync("SetBrightness", v);
        set_by_slider = true;
}

BrightnessSlider::~BrightnessSlider() = default;