//
// Created by simrat39 on 12/23/23.
//

#include "ActiveWindowLabel.hpp"

ActiveWindowLabel::ActiveWindowLabel() {
    this->append(label);
    label.set_ellipsize(Pango::EllipsizeMode::END);
    label.set_text("unknown");
    HyprlandService::get_instance().signal_data_recieved.connect(sigc::mem_fun(*this, &ActiveWindowLabel::update));
}

void ActiveWindowLabel::update(HyprlandService::HyprlandEvent event, std::string data) {
    switch (event) {
        case HyprlandService::ACTIVE_WINDOW:
            if (data.length() > 20) {
                data = data.substr(0, 20) + "...";
            }
            label.set_text(data);
        case HyprlandService::WORKSPACE:
        case HyprlandService::DESTROY_WORKSPACE:
        case HyprlandService::UNKNOWN:
            break;
    }
}

ActiveWindowLabel::~ActiveWindowLabel() = default;
