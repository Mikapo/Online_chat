#pragma once

#include "Application.h"
#include "Key.h"
#include "Message_id.h"
#include "Networking/Net_framework.h"
#include "UI/Ui_controller.h"
#include <array>
#include <thread>

struct Lobby_data;
struct Server_message_data;
class Chat_client : private Net::Client_interface<Message_id>
{
public:
    Chat_client();

    void start();

private:
    void on_message(Net::Net_message<Message_id> net_message) override;
    void setup_callbacks();
    void on_window_open();
    void render();
    void logic_thread();
    void cleanup();
    void on_connect(
        std::string_view username, const std::array<float, 4>& color, std::string_view ip, std::string_view port);
    void send_client_information();
    void on_input(Input_key key, Input_action action);
    void on_send_message(std::string_view message);
    void handle_lobby_information(const Lobby_data& lobby_data);
    void handle_message(const Server_message_data& message);

    Application m_application;
    Ui_controller m_ui_controller;

    std::thread m_logic_thread;
    bool m_logic_thread_stop_flag = false;

    std::string m_username = "";
    std::array<float, 4> m_color = {0.0f, 0.0f, 0.0f, 0.0f};
    bool m_has_send_information = false;
};
