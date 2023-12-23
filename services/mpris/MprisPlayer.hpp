//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include <sigc++/signal.h>
extern "C" {
#include <playerctl.h>
}

class MprisPlayer {
public:
    explicit MprisPlayer(PlayerctlPlayerName* p_name);
    ~MprisPlayer();

    std::string get_title();
    std::string get_artist();
    long get_position();
    long get_length();
    std::string get_metadata(std::string key);

    sigc::signal<void()> signal_update;

    std::string name;
private:
    PlayerctlPlayer* player;
};
