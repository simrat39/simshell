//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>

class RootBar: public Gtk::Window {
public:
    RootBar();
    ~RootBar() override;
protected:
    void on_button_clicked();

    Gtk::Box m_box{};
};
