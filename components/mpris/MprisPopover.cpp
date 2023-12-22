//
// Created by simrat39 on 12/21/23.
//

#include "MprisPopover.hpp"
#include "../../services/mpris/MprisService.hpp"
#include "MprisPage.hpp"

MprisPopover::MprisPopover(): Gtk::Popover() {
    this->set_child(notebook);
    this->set_size_request(400, -1);
    this->notebook.set_size_request(350, -1);

    this->add_css_class("mpris_popover");
}

MprisPopover::~MprisPopover() = default;

void MprisPopover::on_map() {
    Widget::on_map();

    auto players = MprisService::get_instance().players;

    for (const auto& p: players) {
        auto page = new MprisPage{p};
        pages.push_back(page);

        notebook.append_page(*page, p->name);
    }
}

void MprisPopover::on_unmap() {
    Widget::on_unmap();

    auto n_pages = notebook.get_n_pages();
    for (int i = 0; i < n_pages; i++) {
       notebook.remove_page(i);
    }

    for(MprisPage* p: pages) {
        delete p;
    }
    pages.clear();
}
