#include <gudev/gudev.h>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include "SimshellApp.hpp"
#include "services/backlight/BrightnessService.hpp"

static GUdevDevice*
gsd_backlight_udev_get_type (GList *devices, const gchar *type)
{
    const gchar *type_tmp;
    GList *d;

    for (d = devices; d != nullptr; d = d->next) {
        type_tmp = g_udev_device_get_sysfs_attr (G_UDEV_DEVICE (g_object_ref (d->data)), "type");
        if (g_strcmp0 (type_tmp, type) == 0)
            return G_UDEV_DEVICE (g_object_ref (d->data));
    }
    return nullptr;
}


/*
 * Search for a raw backlight interface, raw backlight interfaces registered
 * by the drm driver will have the drm-connector as their parent, check the
 * drm-connector's enabled sysfs attribute so that we pick the right LCD-panel
 * connector on laptops with hybrid-gfx. Fall back to just picking the first
 * raw backlight interface if no enabled interface is found.
 */
static GUdevDevice*
gsd_backlight_udev_get_raw (GList *devices)
{
    GUdevDevice *parent;
    const gchar *attr;
    GList *d;

    for (d = devices; d != nullptr; d = d->next) {
        attr = g_udev_device_get_sysfs_attr (G_UDEV_DEVICE (g_object_ref (d->data)), "type");
        if (g_strcmp0 (attr, "raw") != 0)
            continue;

        parent = g_udev_device_get_parent (G_UDEV_DEVICE(g_object_ref(d->data)));
        if (!parent)
            continue;

        attr = g_udev_device_get_sysfs_attr (parent, "enabled");
        if (!attr || g_strcmp0 (attr, "enabled") != 0)
            continue;

        return G_UDEV_DEVICE (g_object_ref (d->data));
    }

    return gsd_backlight_udev_get_type (devices, "raw");
}

static void
gsd_backlight_udev_uevent (GUdevClient *client, const gchar *action, GUdevDevice *device, gpointer user_data)
{
    std::cout << "UHM" << std::endl;
    g_debug ("GsdBacklight: Got uevent");
}

int main(int argc, char* argv[]) {
    auto app = SimshellApp::create();

//    const gchar* const subsystems[] = {"backlight", nullptr};
//    auto client = g_udev_client_new(subsystems);
//
//    auto devices = g_udev_client_query_by_subsystem(client, "backlight");
//
//    const gchar *type_tmp;
//    GList *d;
//
//    for (d = devices; d != nullptr; d = d->next) {
//        std::cout << g_udev_device_get_name(G_UDEV_DEVICE(d->data)) << std::endl;
//    }
//
//    auto main_device = gsd_backlight_udev_get_raw(devices);
//    std::cout << main_device << std::endl;
//
//    auto max_b = g_udev_device_get_sysfs_attr_as_int(main_device, "max_brightness");
//    std::cout << max_b << std::endl;
//
//    g_signal_connect_object(client, "uevent", G_CALLBACK (gsd_backlight_udev_uevent), main_device,
//                            static_cast<GConnectFlags>(0));
    return app->run(argc, argv);
}
