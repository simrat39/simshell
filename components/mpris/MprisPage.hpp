//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include "../../services/mpris/MprisPlayer.hpp"

class MprisPage: public Gtk::Box {
public:
    explicit MprisPage(MprisPlayer* player);
    ~MprisPage() override;

    Gtk::Image music_art;
private:
    MprisPlayer* player;

    Gtk::Label title;
    Gtk::Label artist;

    void update_data();
};
