//
// Created by simrat39 on 12/24/23.
//

#pragma once

#include <gtkmm/button.h>
#include <gtkmm/eventcontrollermotion.h>
#include <gtkmm/box.h>
#include <gtkmm/popover.h>

class HyprlandWorkspaceButton: public Gtk::Box {
public:
    HyprlandWorkspaceButton(int id, std::string name);
    ~HyprlandWorkspaceButton() override;

    void set_current();
    void unset_current();
    void on_click();
private:
    int id;
    std::string name;
    Gtk::Button button;

    Gtk::Popover popover;

    bool current = false;
};
