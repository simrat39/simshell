//
// Created by simrat39 on 12/20/23.
//

#pragma once

class HyprlandService {
public:
    enum HyprlandEvent {
        WORKSPACE,
        ACTIVE_WINDOW,
        CREATE_WORKSPACE,
        DESTROY_WORKSPACE,
        UNKNOWN
    };

    static HyprlandService get_instance();

    using HyprlandDataSignal = sigc::signal<void(HyprlandEvent, std::string)>;
    HyprlandDataSignal signal_data_recieved;

    std::string hyperctl_request(const char* request);

    ~HyprlandService();
private:
    HyprlandService();

    static std::string get_hypripc_socket();
    void on_hypripc_data(const std::string& data);

    static std::string get_hyprctl_socket();
};

