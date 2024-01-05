//
// Created by simrat39 on 12/20/23.
//

#pragma once

#include <queue>
#include <glibmm/dispatcher.h>

class HyprlandService {
public:
    enum HyprlandEvent {
        WORKSPACE,
        ACTIVE_WINDOW,
        CREATE_WORKSPACE,
        DESTROY_WORKSPACE,
        UNKNOWN
    };

    static HyprlandService &get_instance();

    using HyprlandDataSignal = sigc::signal<void(HyprlandEvent, std::string)>;
    HyprlandDataSignal signal_data_recieved;

    std::string hyperctl_request(const char *request);

    ~HyprlandService();
private:
    HyprlandService();
    HyprlandService(const HyprlandService&) = delete;
    HyprlandService& operator=(const HyprlandService &) = delete;

    static std::string get_hypripc_socket();

    void on_hypripc_data(const std::string &data);

    static std::string get_hyprctl_socket();

    std::queue<std::pair<HyprlandEvent, std::string>> data_queue{};
    std::mutex queue_mutex{};

    void enqueue(HyprlandService::HyprlandEvent event, std::string data);

    void process_queue();

    Glib::Dispatcher dispatcher;
};
