//
// Created by simrat39 on 12/23/23.
//

#include "components/power/PowerPopover.hpp"
#include "components/power/BrightnessSlider.hpp"
#include "gtkmm/builder.h"
#include "gtkmm/object.h"
#include "services/backlight/BacklightService.hpp"

PowerPopover::PowerPopover() {
  this->set_size_request(300, -1);

  this->set_has_arrow(false);
  this->add_css_class("power_popover");

  // Brightness sliders
  auto b_devices = BacklightService::get_instance().get_devices();
  auto dev = G_UDEV_DEVICE(b_devices->data);

  auto ui = Gtk::Builder::create_from_file("../src/ui/power/PowerPopup.xml");

  auto root_box = ui->get_widget<Gtk::Box>("box");
  this->set_child(*root_box);

  brightness_box = ui->get_widget<Gtk::Box>("brightness-box");
}

void PowerPopover::on_map() {
  Widget::on_map();

  auto b_devices = BacklightService::get_instance().get_devices();
  GList *d;
  for (d = b_devices; d != nullptr; d = d->next) {
    auto bs = Gtk::make_managed<BrightnessSlider>(G_UDEV_DEVICE(d->data));
    brightness_sliders.push_back(bs);

    bs->set_hexpand(true);
    brightness_box->append(*bs);
  }
}

void PowerPopover::on_unmap() {
    Widget::on_unmap();

    for (const auto bs: brightness_sliders) {
        brightness_box->remove(*bs);
    }
    brightness_sliders.clear();
}

PowerPopover::~PowerPopover() = default;
