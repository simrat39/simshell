//
// Created by simrat39 on 12/18/23.
//

#include <gtkmm/menubutton.h>
#include <iostream>
#include "RightComponents.hpp"
#include "services/backlight/BacklightService.hpp"

RightComponents::RightComponents(): Gtk::Box() {
    mpris_button = new MprisButton{};
    this->append(*mpris_button);

    this->append(mb);

    auto ctx = mb.get_style_context();
    ctx->add_class("button");

    mb.set_icon_name("display-brightness-symbolic");

    Gtk::Popover pp{};
    pp.set_has_arrow(false);
    pp.set_offset(5, 5);
    pp.get_style_context()->add_class("popover");
    pp.set_size_request(300, -1);
    mb.set_popover(pp);

    auto b_devices = BacklightService::get_instance().get_devices();

    GList *d;

    for (d = b_devices; d != nullptr; d = d->next) {
        auto bs = new BrightnessSlider{G_UDEV_DEVICE(d->data)};
        bs->set_hexpand(true);
        pp.set_child(*bs);

        brightness_sliders.push_back(bs);
    }
}

void RightComponents::on_unmap() {
    for (const auto bs: brightness_sliders) {
        delete bs;
    }
}

void RightComponents::on_map() {
    Widget::on_map();
}

RightComponents::~RightComponents() {
    delete mpris_button;
};
