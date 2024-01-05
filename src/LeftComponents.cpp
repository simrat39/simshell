//
// Created by simrat39 on 12/18/23.
//

#include "../include/LeftComponents.hpp"
#include "components/workspaces/HyprlandWorkspaces.hpp"

LeftComponents::LeftComponents(): Gtk::Box() {
    hpw = Gtk::make_managed<HyprlandWorkspaces>();
    append(*hpw);

    awl = Gtk::make_managed<ActiveWindowLabel>();
    append(*awl);
}

LeftComponents::~LeftComponents() = default;
