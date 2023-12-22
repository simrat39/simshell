//
// Created by simrat39 on 12/21/23.
//

#pragma once

#include "MprisPlayer.hpp"

extern "C" {
#include <playerctl/playerctl.h>
}

class MprisService {
public:
    static MprisService get_instance();
    ~MprisService();

    std::vector<MprisPlayer*> players;
    sigc::signal<void(MprisPlayer*)> signal_new_player;
private:
    MprisService();
    PlayerctlPlayerManager* manager;
};
