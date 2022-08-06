#pragma once

#include "Message_id.h"
#include "Networking/Net_framework.h"
#include <cstdint>
#include <unordered_map>

class Chat_server : private Net::Server_interface<Message_id>
{
public:
    Chat_server(uint16_t port);

    void start();

private:
    void on_notification(std::string_view message, Net::Severity severity) override;
    void on_message(Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message) override;
    void on_client_disconnect(uint32_t id, std::string_view ip) override;
    void handle_client_message(
        Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message);
    void handle_client_set_name(
        Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message);

    std::unordered_map<uint32_t, std::string> m_names;
};
