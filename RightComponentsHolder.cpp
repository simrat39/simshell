//
// Created by simrat39 on 12/18/23.
//

#include <gtkmm/menubutton.h>
#include <iostream>
#include "RightComponentsHolder.hpp"
#include "services/backlight/BrightnessService.hpp"

RightComponentsHolder::RightComponentsHolder(): Gtk::Box() {
    this->append(mb);

    auto ctx = mb.get_style_context();
    ctx->add_class("button");

    mb.set_icon_name("display-brightness-symbolic");
    mb.set_has_frame(false);
    mb.set_focus_on_click(false);

    Gtk::Popover pp{};
    pp.get_style_context()->add_class("popover");
    pp.set_size_request(300, -1);
    mb.set_popover(pp);

    auto b_devices = BrightnessService::get_instance().get_devices();


    GList *d;

    for (d = b_devices; d != nullptr; d = d->next) {
        std::cout << g_udev_device_get_name(G_UDEV_DEVICE(d->data)) << std::endl;

        auto bs = new BrightnessSlider{G_UDEV_DEVICE(d->data)};
        bs->set_hexpand(true);
        pp.set_child(*bs);

        brightness_sliders.push_back(bs);
    }
}

void RightComponentsHolder::on_show() {
    Gtk::Box::on_show();

    mb.show();
}

RightComponentsHolder::~RightComponentsHolder() {
    std::cout << "called btw" << std::endl;
}

void RightComponentsHolder::on_unmap() {
    std::cout << "ermm" << std::endl;

    for (const auto bs: brightness_sliders) {
        delete bs;
    }
};
