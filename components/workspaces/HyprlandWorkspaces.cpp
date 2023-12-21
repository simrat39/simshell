//
// Created by simrat39 on 12/21/23.
//

#include <iostream>
#include "HyprlandWorkspaces.hpp"

HyprlandWorkspaces::HyprlandWorkspaces(): Gtk::Box() {
    HyprlandService::get_instance().signal_data_recieved.connect(sigc::mem_fun(*this, &HyprlandWorkspaces::hyperland_data_cb));
}

HyprlandWorkspaces::~HyprlandWorkspaces() {

}

void HyprlandWorkspaces::hyperland_data_cb(HyprlandService::HyprlandEvent event, const std::string& data) {
    switch (event) {
        case HyprlandService::WORKSPACE:
            workspaces.insert(data);
            break;
        case HyprlandService::ACTIVE_WINDOW:
            break;
        case HyprlandService::DESTROY_WORKSPACE:
            workspaces.erase(data);
            break;
    }
}
