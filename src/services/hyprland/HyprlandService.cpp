//
// Created by simrat39 on 12/20/23.
//

#include <glibmm/main.h>
#include "services/hyprland/HyprlandService.hpp"
#include <sys/un.h>
#include <sys/socket.h>
#include <thread>

HyprlandService& HyprlandService::get_instance() {
    static HyprlandService instance;
    return instance;
}

HyprlandService::HyprlandService() {
    dispatcher.connect([&](){
       this->process_queue();
    });

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
                break;
            } else if (bytesRead == 0) {
                printf("Connection closed by the server\n");
                break;
            } else {
                on_hypripc_data(std::string(buffer, bytesRead));
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
        } else if (e_name == "createworkspace") {
            event = CREATE_WORKSPACE;
        }

        enqueue(event, e_data);
        dispatcher.emit();
    }
}

std::string HyprlandService::get_hyprctl_socket() {
    auto his = std::getenv("HYPRLAND_INSTANCE_SIGNATURE");
    return std::string("/tmp/hypr/") + std::string(his) + std::string("/.socket.sock");
}

std::string HyprlandService::hyperctl_request(const char* request) {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un server_address{};
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, get_hyprctl_socket().c_str());

    // Connect to the server
    if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to socket");
        close(sock);
    }

    if (send(sock, request, strlen(request), 0) == -1) {
        perror("Error sending data to socket");
        close(sock);
        return "";
    }

    std::string ret;

    char buffer[4096];
    ssize_t bytesRead = recv(sock, buffer, sizeof(buffer), 0);

    do {
        if (bytesRead == -1) {
            perror("Error reading from socket");
            close(sock);
            return "";
        } else if (bytesRead == 0) {
            printf("Connection closed by the server\n");
            close(sock);
            return "";
        } else {
            ret.append(buffer, bytesRead);
        }

        bytesRead = recv(sock, buffer, sizeof(buffer), 0);
    } while (bytesRead > 0);

    close(sock);

    return ret;
}

void HyprlandService::enqueue(HyprlandService::HyprlandEvent event, std::string data) {
    std::lock_guard<std::mutex> lock{queue_mutex};
    data_queue.push(std::make_pair(event, data));
}

void HyprlandService::process_queue() {
    std::lock_guard<std::mutex> lock{queue_mutex};

    while (!data_queue.empty()) {
        auto data = data_queue.front();
        data_queue.pop();

        signal_data_recieved.emit(data.first, data.second);
    }
}

HyprlandService::~HyprlandService() = default;
