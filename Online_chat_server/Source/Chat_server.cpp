#include "Chat_server.h"
#include <iostream>

Chat_server::Chat_server(uint16_t port) : Net::Server_interface<Message_id>(port)
{
    add_accepted_message(Message_id::client_message);
    add_accepted_message(Message_id::client_information);
}

void Chat_server::start()
{
    Net::Server_interface<Message_id>::start();

    while (true)
        update(10, true, std::chrono::seconds(10));
}

void Chat_server::on_notification(std::string_view message, Net::Severity severity)
{
    std::cout << message << "\n";
}

void Chat_server::on_message(Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message)
{
    switch (message.get_id())
    {
    case Message_id::client_message:
        handle_client_message(client, std::move(message));
        break;

    case Message_id::client_information:
        handle_client_information(client, std::move(message));
        break;

    default:
        client.disconnect();
        break;
    }
}

void Chat_server::on_client_disconnect(uint32_t id, std::string_view ip)
{
    auto found_client = m_clients.find(id);

    if (found_client != m_clients.end())
    {
        auto net_message = Net_message_converter::packade_server_client_left(found_client->second);
        send_message_to_all_clients(net_message);
        m_clients.erase(found_client);
    }
}

void Chat_server::handle_client_message(
    Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message)
{
    auto found_client = m_clients.find(client.get_id());

    if (found_client == m_clients.end())
    {
        client.disconnect();
        return;
    }

    Server_message_data message_data;
    message_data.m_message = Net_message_converter::extract_client_message(message);
    message_data.m_sender_id = found_client->second.m_id;
    message_data.m_sender_name = found_client->second.m_name;
    message_data.m_sender_color = found_client->second.m_color;
    message_data.m_send_time = std::chrono::utc_clock::now();

    auto server_message = Net_message_converter::package_server_message(message_data);
    send_message_to_all_clients(server_message);
}

void Chat_server::handle_client_information(
    Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message)
{
    const Client_data client_data = Net_message_converter::extract_client_information(message, client.get_id());
    m_clients[client_data.m_id] = client_data;

    auto join_net_message = Net_message_converter::packade_server_client_join(client_data);
    send_message_to_all_clients(join_net_message, client);

    auto lobby_information_net_message = Net_message_converter::packade_server_lobby_information(m_clients);
    send_message_to_client(client, lobby_information_net_message);
}
