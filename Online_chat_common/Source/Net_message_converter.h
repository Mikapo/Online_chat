#pragma once

#include "Message_id.h"
#include "Networking/Utility/Net_message.h"
#include <unordered_map>

struct Client_data
{
    uint32_t m_client_id = 0;
    std::string m_client_name = "";
};

struct Server_message_data
{
    uint32_t m_sender_id = 0;
    std::string m_sender_name = "";
    std::string m_message = "";
};

struct Lobby_data
{
    std::vector<Client_data> m_clients;
};

class Net_message_converter
{
public:
    static Net::Net_message<Message_id> packade_server_lobby_information(
        const std::unordered_map<uint32_t, std::string>& clients)
    {
        Net::Net_message<Message_id> net_message;
        net_message.set_id(Message_id::server_lobby_information);

        for (const auto& client : clients)
        {
            net_message.push_back_from_container(client.second.begin(), client.second.end());
            net_message << static_cast<uint64_t>(client.second.size());
            net_message << client.first;
        }

        net_message << static_cast<uint64_t>(clients.size());

        return net_message;
    }

    static Lobby_data extract_server_lobby_information(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_lobby_information)
            throw std::runtime_error("Wrong type of message");

        uint64_t size = 0;
        in_net_message >> size;

        Lobby_data output;
        output.m_clients.reserve(size);

        for (uint64_t i = 0; i < size; ++i)
        {
            auto& current = output.m_clients.emplace_back();
            in_net_message >> current.m_client_id;

            uint64_t name_size;
            in_net_message >> name_size;

            current.m_client_name = in_net_message.extract_as_string(name_size);
        }

        return output;
    }

    static Net::Net_message<Message_id> packade_server_client_left(
        uint32_t client_id, std::string_view client_name = "Client")
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::server_client_left);
        net_message.push_back_from_container(client_name.begin(), client_name.end());
        net_message << client_id;
        return net_message;
    }

    static Client_data extract_server_client_left(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_client_left)
            throw std::runtime_error("Wrong type of message");

        Client_data data;
        in_net_message >> data.m_client_id;
        data.m_client_name = in_net_message.extract_as_string();
        return data;
    }

    static Net::Net_message<Message_id> packade_server_client_join(
        uint32_t client_id, std::string_view client_name = "Client")
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::server_client_join);
        net_message.push_back_from_container(client_name.begin(), client_name.end());
        net_message << client_id;
        return net_message;
    }

    static Client_data extract_server_client_join(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_client_join)
            throw std::runtime_error("Wrong type of message");

        Client_data data;
        in_net_message >> data.m_client_id;
        data.m_client_name = in_net_message.extract_as_string();
        return data;
    }

    static Net::Net_message<Message_id> packade_client_set_name(std::string_view nickname)
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::client_set_name);
        net_message.push_back_from_container(nickname.begin(), nickname.end());
        return net_message;
    }

    static std::string extract_client_set_name(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::client_set_name)
            throw std::runtime_error("Wrong type of message");

        return in_net_message.extract_as_string();
    }

    static Net::Net_message<Message_id> package_client_message(std::string_view message)
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::client_message);
        net_message.push_back_from_container(message.begin(), message.end());
        return net_message;
    }

    static std::string extract_client_message(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::client_message)
            throw std::runtime_error("Wrong type of message");

        return in_net_message.extract_as_string();
    }

    static Net::Net_message<Message_id> package_server_message(
        std::string_view message, uint32_t sender_id, std::string_view sender = "Client")
    {
        Net::Net_message<Message_id> net_message;
        net_message.set_id(Message_id::server_message);
        net_message.push_back_from_container(message.begin(), message.end());
        net_message.push_back_from_container(sender.begin(), sender.end());
        net_message << static_cast<uint64_t>(sender.size());
        net_message << sender_id;
        return net_message;
    }

    static Server_message_data extract_server_message(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_message)
            throw std::runtime_error("Wrong type of message");

        Server_message_data data;
        in_net_message >> data.m_sender_id;

        uint64_t sender_name__size;
        in_net_message >> sender_name__size;

        data.m_sender_name = in_net_message.extract_as_string(sender_name__size);
        data.m_message = in_net_message.extract_as_string();

        return data;
    }
};
