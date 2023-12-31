//
// Created by simrat39 on 12/21/23.
//

#include <giomm/dbusconnection.h>
#include <iostream>
#include "services/mpris/MprisService.hpp"
#include "services/mpris/MprisPlayer.hpp"

extern "C" {
#include <playerctl.h>
}

MprisService& MprisService::get_instance() {
    static MprisService instance;
    return instance;
}

MprisService::~MprisService() = default;

void on_new_player(PlayerctlPlayerManager* manager, PlayerctlPlayerName* player_name,
                                 gpointer data) {
    auto mpris = reinterpret_cast<MprisService*>(data);

    auto new_player = new MprisPlayer{player_name};
    mpris->players.push_back(new_player);

    mpris->signal_new_player.emit(new_player);
}

void on_player_remove(PlayerctlPlayerManager* manager, PlayerctlPlayerName* player_name,
                   gpointer data) {
    auto mpris = reinterpret_cast<MprisService*>(data);

    auto iter = mpris->players.begin();
    auto end = mpris->players.end();
    while (iter != end) {
        if ((*iter)->name == std::string{player_name->name}) {
            mpris->players.erase(iter);
            break;
        }
        iter++;
    }
}

MprisService::MprisService() {
    manager = playerctl_player_manager_new(nullptr);

    GList* cur_player_names = playerctl_list_players(nullptr);
    for (GList* iter = cur_player_names; iter != NULL; iter = iter->next) {
        auto name = static_cast<PlayerctlPlayerName*>(iter->data);

        auto new_player = new MprisPlayer{name};
        this->players.push_back(new_player);
    }

    g_signal_connect(manager, "name-appeared", G_CALLBACK(on_new_player), this);
    g_signal_connect(manager, "name-vanished", G_CALLBACK(on_player_remove), this);
}
