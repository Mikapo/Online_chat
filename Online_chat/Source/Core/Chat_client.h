#pragma once

#include "Application.h"
#include "Message_id.h"
#include "Networking/Net_framework.h"
#include "UI/Ui_controller.h"
#include <thread>

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
    void on_connect(std::string_view username, std::string_view ip, std::string_view port);
    void send_username();
    void on_send_message(std::string_view message);

    Application m_application;
    Ui_controller m_ui_controller;

    std::thread m_logic_thread;
    bool m_logic_thread_stop_flag = false;

    std::string m_username = "";
    bool m_has_send_username = false;
};
