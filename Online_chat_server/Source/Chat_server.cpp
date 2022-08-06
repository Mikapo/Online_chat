#include "Chat_server.h"
#include "Net_message_converter.h"
#include <iostream>

Chat_server::Chat_server(uint16_t port) : Net::Server_interface<Message_id>(port)
{
    add_accepted_message(Message_id::client_message);
    add_accepted_message(Message_id::client_set_name);
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

    case Message_id::client_set_name:
        handle_client_set_name(client, std::move(message));
        break;

    default:
        client.disconnect();
        break;
    }
}

void Chat_server::on_client_disconnect(uint32_t id, std::string_view ip)
{
    auto found_name = m_names.find(id);

    std::string name = "Client";

    if (found_name != m_names.end())
    {
        name = found_name->second;
        m_names.erase(found_name);
    }

    auto net_message = Net_message_converter::packade_server_client_left(id, name);
    send_message_to_all_clients(net_message);
}

void Chat_server::handle_client_message(
    Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message)
{
    std::string name = "Client";

    auto found_name = m_names.find(client.get_id());

    if (found_name != m_names.end())
        name = found_name->second;

    const std::string chat_message = Net_message_converter::extract_client_message(message);

    std::cout << chat_message << "\n";

    auto server_message = Net_message_converter::package_server_message(chat_message, client.get_id(), name);

    send_message_to_all_clients(server_message);
}

void Chat_server::handle_client_set_name(
    Net::Client_connection_interface<Message_id> client, Net::Net_message<Message_id> message)
{
    const std::string name = Net_message_converter::extract_client_set_name(message);
    const uint32_t id = client.get_id();
    m_names[id] = name;

    auto net_message = Net_message_converter::packade_server_client_join(id, name);
    send_message_to_all_clients(net_message);
}
