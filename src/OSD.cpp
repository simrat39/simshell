#include "OSD.hpp"
#include "glibmm/main.h"
#include "gtk4-layer-shell.h"
#include "gtkmm/builder.h"
#include "gtkmm/progressbar.h"
#include "gtkmm/revealer.h"
#include "gtkmm/window.h"
#include "services/backlight/BacklightService.hpp"

OSD::OSD() : Gtk::Window() {
  // Initialize layer shell protocol
  gtk_layer_init_for_window(this->gobj());
  gtk_layer_set_layer(this->gobj(),
                      GtkLayerShellLayer::GTK_LAYER_SHELL_LAYER_OVERLAY);
  // gtk_layer_auto_exclusive_zone_enable(this->gobj());

  // The margins are the gaps around the window's edges
  gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, 0);
  gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, 0);
  gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, 0);
  gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM,
                       150); // 0 is default

  // Pin to the bottom
  static const gboolean anchors[] = {FALSE, FALSE, FALSE, TRUE};
  for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
    gtk_layer_set_anchor(this->gobj(), static_cast<GtkLayerShellEdge>(i),
                         anchors[i]);
  }

  auto ui = Gtk::Builder::create_from_file("../src/ui/osd/BrightnessOSD.xml");
  revealer = ui->get_widget<Gtk::Revealer>("revealer");
  progress = ui->get_widget<Gtk::ProgressBar>("progress");

  this->set_child(*revealer);

  // Backlight
  BacklightService::get_instance().add_listener(
      "OSD", [this](GUdevClient *, const gchar *, GUdevDevice *device,
                    BacklightService *) {
        auto max_brightness =
            g_udev_device_get_sysfs_attr_as_int(device, "max_brightness");
        auto cur_brightness =
            g_udev_device_get_sysfs_attr_as_int(device, "brightness");

        progress->set_fraction((double)cur_brightness / max_brightness);
        revealer->set_reveal_child(true);

        this->timeout.disconnect();
        this->timeout = Glib::signal_timeout().connect(
            [this]() {
              revealer->set_reveal_child(false);
              return false;
            },
            2000);
      });
}

OSD::~OSD() = default;
