//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/progressbar.h>
#include <libsoup/soup-session.h>
#include "../../services/mpris/MprisPlayer.hpp"

class MprisPage: public Gtk::Box {
public:
    explicit MprisPage(MprisPlayer* player);
    ~MprisPage() override;

    Gtk::Image music_art;

    SoupSession* soup_session;
    SoupMessage* soup_message;
private:
    MprisPlayer* player;

    Gtk::Label title;
    Gtk::Label artist;
    Gtk::ProgressBar progress;

    void update_data();
};
