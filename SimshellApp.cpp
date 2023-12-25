//
// Created by simrat39 on 12/18/23.
//

#include <gtk4-layer-shell.h>
#include <iostream>
#include <gtkmm/cssprovider.h>
#include "SimshellApp.hpp"
#include "RootBar.hpp"
#include "services/hyprland/HyprlandService.hpp"
#include "services/mpris/MprisService.hpp"

SimshellApp::SimshellApp() : Gtk::Application("simtim.app") {}

void SimshellApp::on_activate() {
    auto root_bar = new RootBar();
    add_window(*root_bar);

    // Initialize layer shell protocol
    gtk_layer_init_for_window(root_bar->gobj());
    gtk_layer_auto_exclusive_zone_enable(root_bar->gobj());

    // Don't grab keyboard focus
//    gtk_layer_set_keyboard_mode(root_bar->gobj(), GTK_LAYER_SHELL_KEYBOARD_MODE_NONE);

    // The margins are the gaps around the window's edges
    gtk_layer_set_margin(root_bar->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, 10);
    gtk_layer_set_margin(root_bar->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, 10);
    gtk_layer_set_margin(root_bar->gobj(), GTK_LAYER_SHELL_EDGE_TOP, 10);
    gtk_layer_set_margin(root_bar->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, 10); // 0 is default

    // Pin to top, left and right for a top bar
    static const gboolean anchors[] = {TRUE, TRUE, TRUE, FALSE};
    for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
        gtk_layer_set_anchor(root_bar->gobj(), static_cast<GtkLayerShellEdge>(i), anchors[i]);
    }

    // Global styling
    auto provider = Gtk::CssProvider::create();
    provider->load_from_file(Gio::File::create_for_path("../styles.css"));
    Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), provider,
                                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    // Start listening to MPRIS events
    MprisService::get_instance();

    // Show root window
    root_bar->present();
    root_bar->show();
}

Glib::RefPtr<SimshellApp> SimshellApp::create() {
    return Glib::make_refptr_for_instance<SimshellApp>(new SimshellApp());
}