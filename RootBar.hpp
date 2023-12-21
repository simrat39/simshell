//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include "RightComponents.hpp"
#include "CenterComponents.hpp"

class RootBar: public Gtk::Window {
public:
    RootBar();
    ~RootBar() override;
protected:
    Gtk::Box m_box{};

    CenterComponents* center;
    RightComponents* right;
};
