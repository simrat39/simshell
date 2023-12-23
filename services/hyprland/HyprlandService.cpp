//
// Created by simrat39 on 12/20/23.
//

#include <iostream>
#include <glibmm/main.h>
#include "HyprlandService.hpp"
#include <sys/un.h>
#include <sys/socket.h>
#include <thread>

HyprlandService HyprlandService::get_instance() {
    static HyprlandService instance;
    return instance;
}

HyprlandService::HyprlandService() {
    std::thread{[this]() {
        int sock = socket(AF_UNIX, SOCK_STREAM, 0);

        struct sockaddr_un server_address{};
        server_address.sun_family = AF_UNIX;
        strcpy(server_address.sun_path, get_hypripc_socket().c_str());

        // Connect to the server
        if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
            perror("Error connecting to socket");
            close(sock);
        }

        while (true) {
            char buffer[4096];
            ssize_t bytesRead = recv(sock, buffer, sizeof(buffer), 0);

            if (bytesRead == -1) {
                perror("Error reading from socket");
            } else if (bytesRead == 0) {
                printf("Connection closed by the server\n");
            } else {
                on_hypripc_data(std::string(buffer, bytesRead));
            }
        }
    }}.detach();
}

std::string HyprlandService::get_hypripc_socket() {
    auto his = std::getenv("HYPRLAND_INSTANCE_SIGNATURE");
    return std::string("/tmp/hypr/") + std::string(his) + std::string("/.socket2.sock");
}

void HyprlandService::on_hypripc_data(const std::string &data) {
    std::stringstream ss{data};
    std::string ref;

    while (std::getline(ss, ref, '\n')) {
        const auto delim = ref.find(">>");
        const auto e_name = ref.substr(0, delim);
        const auto e_data = ref.substr(delim + 2);

        HyprlandEvent event = UNKNOWN;

        if (e_name == "workspace") {
            event = WORKSPACE;
        } else if (e_name == "activewindow") {
            event = ACTIVE_WINDOW;
        } else if (e_name == "destroyworkspace") {
            event = DESTROY_WORKSPACE;
        } else if (e_name == "openlayer") {}

        signal_data_recieved.emit(event, e_data);
    }
}

HyprlandService::~HyprlandService() = default;
