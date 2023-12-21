//
// Created by simrat39 on 12/18/23.
//

#include <gtk4-layer-shell.h>
#include <iostream>
#include <gtkmm/cssprovider.h>
#include "SimshellApp.hpp"
#include "RootBar.hpp"

SimshellApp::SimshellApp(): Gtk::Application("simtim.app") {}

void SimshellApp::on_activate() {
    auto root_bar = new RootBar();
    add_window(*root_bar);

    gtk_layer_init_for_window(root_bar->gobj());
    gtk_layer_auto_exclusive_zone_enable(root_bar->gobj());

    gtk_layer_set_keyboard_mode(root_bar->gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_NONE);

    // The margins are the gaps around the window's edges
    // Margins and anchors can be set like this...
    gtk_layer_set_margin (root_bar->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, 5);
    gtk_layer_set_margin (root_bar->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, 5);
    gtk_layer_set_margin (root_bar->gobj(), GTK_LAYER_SHELL_EDGE_TOP, 5);
    gtk_layer_set_margin (root_bar->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, 0); // 0 is default

    // ... or like this
    // Anchors are if the window is pinned to each edge of the output
    static const gboolean anchors[] = {TRUE, TRUE, TRUE, FALSE};
    for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
        gtk_layer_set_anchor (root_bar->gobj(), static_cast<GtkLayerShellEdge>(i), anchors[i]);
    }

    auto provider = Gtk::CssProvider::create();
    provider->load_from_file(Gio::File::create_for_path("../styles.css"));

    auto ctx = root_bar->get_style_context();
    Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    root_bar->present();
    root_bar->show();
}

Glib::RefPtr<SimshellApp> SimshellApp::create() {
    return Glib::make_refptr_for_instance<SimshellApp>(new SimshellApp());
}
