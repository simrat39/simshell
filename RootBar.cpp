//
// Created by simrat39 on 12/18/23.
//

#include "RootBar.hpp"
#include "RightComponents.hpp"
#include "CenterComponents.hpp"

RootBar::RootBar() {
    this->set_child(m_box);

    Gtk::Button b1{"L"};
    center = new CenterComponents{};
    right = new RightComponents{};

    Gtk::Box mt1{};
    mt1.set_halign(Gtk::Align::FILL);
    mt1.set_hexpand(true);

    Gtk::Box mt2{};
    mt2.set_halign(Gtk::Align::FILL);
    mt2.set_hexpand(true);

    m_box.append(b1);
    m_box.append(mt1);
    m_box.append(*center);
    m_box.append(mt2);
    m_box.append(*right);

    m_box.show();
}

RootBar::~RootBar() {
    delete center;
    delete right;
};