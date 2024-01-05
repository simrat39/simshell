//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include <gtkmm/popover.h>
#include <gtkmm/notebook.h>
#include "MprisPage.hpp"

class MprisPopover: public Gtk::Popover {
public:
    MprisPopover();
    ~MprisPopover() override;
protected:
    void on_map() override;
    void on_unmap() override;
private:
    Gtk::Notebook notebook;
    std::vector<MprisPage*> pages;
};
