//
// Created by simrat39 on 12/23/23.
//

#include "ActiveWindowLabel.hpp"

ActiveWindowLabel::ActiveWindowLabel() {
    this->add_css_class("active_window");

    label.set_ellipsize(Pango::EllipsizeMode::END);
    label.set_text("unknown");
    label.add_css_class("active_window_label");
    this->append(label);

    HyprlandService::get_instance().signal_data_recieved.connect(sigc::mem_fun(*this, &ActiveWindowLabel::update));
}

void ActiveWindowLabel::update(HyprlandService::HyprlandEvent event, std::string data) {
    switch (event) {
        case HyprlandService::ACTIVE_WINDOW: {
            auto comma = data.find(",");
            auto title = data.substr(comma + 1);
            if (title.length() > 30) {
                title = title.substr(0, 30) + "...";
            }
            label.set_text(title);
            break;
        }
        case HyprlandService::WORKSPACE:
        case HyprlandService::DESTROY_WORKSPACE:
        case HyprlandService::UNKNOWN:
        case HyprlandService::CREATE_WORKSPACE:
            break;
    }
}

ActiveWindowLabel::~ActiveWindowLabel() = default;
