//
// Created by simrat39 on 12/18/23.
//

#pragma once

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include "RightComponents.hpp"
#include "CenterComponents.hpp"
#include "LeftComponents.hpp"
#include "services/mpris/MprisPlayer.hpp"

class RootBar: public Gtk::Window {
public:
    RootBar();
    ~RootBar() override;
protected:
    Gtk::Box m_box{};

    LeftComponents* left;
    CenterComponents* center;
    RightComponents* right;
};
