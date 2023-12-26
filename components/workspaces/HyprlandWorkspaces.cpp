//
// Created by simrat39 on 12/21/23.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include "HyprlandWorkspaces.hpp"

HyprlandWorkspaces::HyprlandWorkspaces() : Gtk::Box() {
    this->add_css_class("workspaces");
    auto& service = HyprlandService::get_instance();

    auto workspaces_json = service.hyperctl_request("j/workspaces");
    auto parsed_json = nlohmann::json::parse(workspaces_json);

    auto cur_workspace = service.hyperctl_request("j/activeworkspace");
    auto cur_workspace_parsed = nlohmann::json::parse(cur_workspace);

    for (const auto &ws: parsed_json) {
        int id = ws["id"];
        std::string name = ws["name"];
        auto pair = std::make_pair(id, name);
        workspaces.push_back(pair);
    }

    std::sort(workspaces.begin(), workspaces.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.first < rhs.first;
    });

    for (const auto &n: workspaces) {
        auto widget = Gtk::make_managed<HyprlandWorkspaceButton>(n.first, n.second);
        if (n.first == cur_workspace_parsed["id"]) {
            widget->set_current();
        }
        ws_widgets.push_back(widget);
    }

    for (auto &w: ws_widgets) {
        w->add_css_class("ws_button");
        append(*w);
    }

    service.signal_data_recieved.connect(sigc::mem_fun(*this, &HyprlandWorkspaces::hyperland_data_cb));
}

HyprlandWorkspaces::~HyprlandWorkspaces() = default;

void HyprlandWorkspaces::hyperland_data_cb(HyprlandService::HyprlandEvent event, const std::string &data) {
    std::lock_guard{mutex};

    switch (event) {
        case HyprlandService::WORKSPACE: {
            int id = std::stoi(data);

            for (int i = 0; i < workspaces.size(); i++) {
                if (workspaces.at(i).first == id) {
                    ws_widgets.at(i)->set_current();
                } else {
                    ws_widgets.at(i)->unset_current();
                }
            }
            break;
        }
        case HyprlandService::ACTIVE_WINDOW:
            break;
        case HyprlandService::CREATE_WORKSPACE: {
            auto workspaces_json = HyprlandService::get_instance().hyperctl_request("j/workspaces");
            auto parsed_json = nlohmann::json::parse(workspaces_json);
            int id = -1;
            std::string name;

            for (const auto &ws: parsed_json) {
                int ws_id = ws["id"];
                std::string ws_name = ws["name"];

                if (ws_name == data) {
                    id = ws_id;
                    name = ws_name;
                    break;
                }
            }

            auto idx = -1;
            if (id < workspaces.at(0).first) {
                idx = 0;
            } else if (id > workspaces.at(workspaces.size() - 1).first) {
                idx = workspaces.size();
            } else {
                for (int i = 0; i < workspaces.size() - 1; ++i) {
                    if (id > workspaces.at(i).first && id < workspaces.at(i + 1).first) {
                        idx = i + 1;
                        break;
                    }
                }
            }

            workspaces.insert(workspaces.begin() + idx, std::make_pair(id, name));

            auto b = Gtk::make_managed<HyprlandWorkspaceButton>(id, name);

            if (idx == 0) {
                this->insert_child_at_start(*b);
            } else {
                this->insert_child_after(*b, *ws_widgets.at(idx - 1));
            }
            ws_widgets.insert(ws_widgets.begin() + idx, b);

            break;
        }
        case HyprlandService::DESTROY_WORKSPACE: {
            int id = -1;
            std::string name;

            for (const auto &ws: workspaces) {
                if (ws.second == data) {
                    id = ws.first;
                    name = ws.second;
                    break;
                }
            }

            int idx = -1;

            for (int i = 0; i < workspaces.size(); ++i) {
                if (id == workspaces.at(i).first) {
                    idx = i;
                    break;
                }
            }

            workspaces.erase(workspaces.begin() + idx);
            auto rm_widget = ws_widgets.at(idx);
            ws_widgets.erase(ws_widgets.begin() + idx);
            this->remove(*rm_widget);

            break;
        }
        case HyprlandService::UNKNOWN:
            break;
    }
}
