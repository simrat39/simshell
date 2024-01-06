//
// Created by simrat39 on 12/21/23.
//

#include <gtkmm/label.h>
#include <glibmm.h>
#include <libsoup-3.0/libsoup/soup-session.h>

#include "components/mpris/MprisPage.hpp"

MprisPage::MprisPage(MprisPlayer *player) : player(player), Gtk::Box() {
    Gtk::Box tr{};
    tr.add_css_class("mpris_page_img_info_row");

    music_art.set_size_request(100, 100);
    music_art.set_halign(Gtk::Align::FILL);
    music_art.set_valign(Gtk::Align::FILL);
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

    progress.set_fraction(0);
    progress.add_css_class("mpris_page_progress");

    this->add_css_class("mpris_page");
    this->set_orientation(Gtk::Orientation::VERTICAL);
    this->append(tr);
    this->append(progress);

    player->signal_update.connect(sigc::mem_fun(*this, &MprisPage::update_data));
    update_data();
}

void on_image_request_finish(GObject *source, GAsyncResult *result, gpointer user_data) {
    auto mpris_page = reinterpret_cast<MprisPage *>(user_data);
    GBytes *bytes = soup_session_send_and_read_finish(SOUP_SESSION(source), result, nullptr);

    if (bytes != nullptr) {
        auto tex = Gdk::Texture::create_from_bytes(
                Glib::Bytes::create(g_bytes_get_data(bytes, nullptr), g_bytes_get_size(bytes)));
        mpris_page->music_art.set(tex);
    }

    g_bytes_unref(bytes);
    g_object_unref(mpris_page->soup_message);
    g_object_unref(mpris_page->soup_session);
}

void MprisPage::update_data() {
    title.set_label(player->get_title());
    artist.set_label(player->get_artist());

    if (player->get_length() != 0) {
        progress.set_fraction((double)player->get_position() / (double)player->get_length());
    }

    auto artUrl = player->get_metadata("mpris:artUrl");
    auto schema = Glib::uri_parse_scheme(artUrl);

    if (!artUrl.empty()) {
        if (schema == "https" || schema == "http") {
            soup_session = soup_session_new();
            soup_message = soup_message_new(SOUP_METHOD_GET, artUrl.c_str());

            soup_session_send_and_read_async(soup_session, soup_message, G_PRIORITY_DEFAULT, nullptr, on_image_request_finish, this);
        } else if (schema == "file") {
            auto file = artUrl.substr(strlen("file://"));
            music_art.set(file);
        }
    }
}


MprisPage::~MprisPage() = default;
