//
// Created by simrat39 on 12/21/23.
//

#include "components/mpris/MprisPopover.hpp"
#include "services/mpris/MprisService.hpp"
#include "components/mpris/MprisPage.hpp"

MprisPopover::MprisPopover(): Gtk::Popover() {
    this->set_has_arrow(false);
    this->set_offset(5, 5);
    this->set_size_request(400, -1);
    this->add_css_class("mpris_popover");

    this->notebook.set_size_request(350, -1);
    this->set_child(notebook);
}

MprisPopover::~MprisPopover() = default;

void MprisPopover::on_map() {
    Widget::on_map();

    auto players = MprisService::get_instance().players;

    for (const auto& p: players) {
        auto page = Gtk::make_managed<MprisPage>(p);

        notebook.append_page(*page, p->name);
    }
}

void MprisPopover::on_unmap() {
    Widget::on_unmap();

    auto n_pages = notebook.get_n_pages();
    for (int i = 0; i < n_pages; i++) {
       notebook.remove_page(i);
    }
    notebook.remove_page(-1);
}
