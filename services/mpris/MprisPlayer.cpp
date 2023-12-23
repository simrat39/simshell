//
// Created by simrat39 on 12/21/23.
//

#include <iostream>
#include "MprisPlayer.hpp"

void on_player_play(gpointer, gpointer data) {
    auto mpris = reinterpret_cast<MprisPlayer*>(data);
    mpris->signal_update.emit();
}

void on_player_pause(gpointer, gpointer data) {
    auto mpris = reinterpret_cast<MprisPlayer*>(data);
    mpris->signal_update.emit();
}

void on_player_metadata(gpointer, gpointer, gpointer data) {
    auto mpris = reinterpret_cast<MprisPlayer*>(data);
    mpris->signal_update.emit();
}

MprisPlayer::MprisPlayer(PlayerctlPlayerName *p_name): name(std::string{p_name->name}) {
    this->player = playerctl_player_new_from_name(p_name, nullptr);

    playerctl_player_on(player, "play", g_cclosure_new(G_CALLBACK(on_player_play), this, nullptr), nullptr);
    playerctl_player_on(player, "pause", g_cclosure_new(G_CALLBACK(on_player_pause), this, nullptr), nullptr);
    playerctl_player_on(player, "metadata", g_cclosure_new(G_CALLBACK(on_player_metadata), this, nullptr), nullptr);
}

std::string MprisPlayer::get_title() {
    return std::string{playerctl_player_get_title(player, nullptr)};
}

std::string MprisPlayer::get_artist() {
    return std::string{playerctl_player_get_artist(player, nullptr)};
}

std::string MprisPlayer::get_metadata(std::string key) {
    return std::string{playerctl_player_print_metadata_prop(player, key.c_str(), nullptr)};
}

long MprisPlayer::get_position() {
    return playerctl_player_get_position(player, nullptr);
}

long MprisPlayer::get_length() {
    return std::stol(get_metadata("mpris:length"));
}

MprisPlayer::~MprisPlayer() = default;
