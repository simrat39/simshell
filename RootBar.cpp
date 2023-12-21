//
// Created by simrat39 on 12/18/23.
//

#include "RootBar.hpp"
#include "RightComponentsHolder.hpp"

RootBar::RootBar() {
    this->set_child(m_box);

    Gtk::Button b1{"L"};
    Gtk::Button b2{"C"};
    RightComponentsHolder right{};

    Gtk::Box mt1{};
    mt1.set_halign(Gtk::Align::FILL);
    mt1.set_hexpand(true);

    Gtk::Box mt2{};
    mt2.set_halign(Gtk::Align::FILL);
    mt2.set_hexpand(true);

    m_box.append(b1);
    m_box.append(mt1);
    m_box.append(b2);
    m_box.append(mt2);
    m_box.append(right);

    b1.show();
    b2.show();
    right.show();
    m_box.show();
}

RootBar::~RootBar() = default;

void RootBar::on_button_clicked() {

}
