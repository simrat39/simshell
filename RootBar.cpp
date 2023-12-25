//
// Created by simrat39 on 12/18/23.
//

#include "RootBar.hpp"
#include "RightComponents.hpp"
#include "CenterComponents.hpp"

RootBar::RootBar() {
    left = Gtk::make_managed<LeftComponents>();
    left->set_hexpand(true);
    left->set_halign(Gtk::Align::START);

//    center = Gtk::make_managed<CenterComponents>();
//    center->set_hexpand(true);
//    center->set_halign(Gtk::Align::CENTER);

    right = Gtk::make_managed<RightComponents>();
    right->set_hexpand(true);
    right->set_halign(Gtk::Align::END);

    m_box.append(*left);
//    m_box.append(*center);
    m_box.append(*right);

    m_box.set_homogeneous();
    this->set_child(m_box);
}

RootBar::~RootBar() = default;