//
// Created by simrat39 on 12/18/23.
//

#include "LeftComponents.hpp"
#include "components/workspaces/HyprlandWorkspaces.hpp"

LeftComponents::LeftComponents(): Gtk::Box() {
    hpw = new HyprlandWorkspaces();
    append(*hpw);
}

LeftComponents::~LeftComponents() {
    delete hpw;
};
