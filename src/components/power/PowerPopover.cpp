//
// Created by simrat39 on 12/23/23.
//

#include "components/power/PowerPopover.hpp"
#include "services/backlight/BacklightService.hpp"

PowerPopover::PowerPopover() {
    content.set_orientation(Gtk::Orientation::VERTICAL);
    this->set_child(content);

    this->set_offset(5, 5);
    this->set_size_request(300, -1);

    this->set_has_arrow(false);
    this->add_css_class("power_popover");
}

PowerPopover::~PowerPopover() = default;

void PowerPopover::on_map() {
    Widget::on_map();

    // Brightness sliders
    auto b_devices = BacklightService::get_instance().get_devices();
    GList *d;
    for (d = b_devices; d != nullptr; d = d->next) {
        auto bs = Gtk::make_managed<BrightnessSlider>(G_UDEV_DEVICE(d->data));
        brightness_sliders.push_back(bs);

        bs->set_hexpand(true);
        content.append(*bs);
    }
    //
}

void PowerPopover::on_unmap() {
    Widget::on_unmap();

    for (const auto bs: brightness_sliders) {
        content.remove(*bs);
    }
    brightness_sliders.clear();
}
