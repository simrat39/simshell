//
// Created by simrat39 on 12/21/23.
//

#include <gtkmm/label.h>
#include <iostream>
#include "MprisPage.hpp"
#include <libsoup-3.0/libsoup/soup-session.h>
#include <iomanip>
#include <fstream>

MprisPage::MprisPage(MprisPlayer *player) : player(player), Gtk::Box() {
    this->add_css_class("mpris_page");

    Gtk::Box tr{};
    tr.add_css_class("mpris_page_img_info_row");
    this->append(tr);

    music_art.set_size_request(100, 100);
    tr.append(music_art);

    Gtk::Box title_author_col{};
    title_author_col.add_css_class("mpris_page_title_author_col");
    title_author_col.set_orientation(Gtk::Orientation::VERTICAL);
    title_author_col.append(title);
    title_author_col.append(artist);

    title.set_halign(Gtk::Align::START);
    title.set_valign(Gtk::Align::START);

    artist.set_halign(Gtk::Align::START);
    artist.set_valign(Gtk::Align::START);

    tr.append(title_author_col);

    tr.set_orientation(Gtk::Orientation::HORIZONTAL);

    player->signal_update.connect(sigc::mem_fun(*this, &MprisPage::update_data));

    update_data();
}

void on_image_request_finish(GObject *source, GAsyncResult *result, gpointer user_data) {
    auto mpris_page = reinterpret_cast<MprisPage *>(user_data);
    GBytes *bytes = soup_session_send_and_read_finish(SOUP_SESSION(source), result, nullptr);

    auto tex = Gdk::Texture::create_from_bytes(
            Glib::Bytes::create(g_bytes_get_data(bytes, nullptr), g_bytes_get_size(bytes)));
    mpris_page->music_art.set(tex);
}

void MprisPage::update_data() {
    title.set_label(player->get_title());
    artist.set_label(player->get_artist());

    auto artUrl = player->get_metadata("mpris:artUrl");
    if (!artUrl.empty()) {
        SoupSession *session = soup_session_new();
        SoupMessage *msg = soup_message_new(SOUP_METHOD_GET, artUrl.c_str());

        soup_session_send_and_read_async(session, msg, G_PRIORITY_DEFAULT, nullptr, on_image_request_finish, this);
    }
}

MprisPage::~MprisPage() = default;
