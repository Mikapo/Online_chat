#pragma once

#include "Message_id.h"
#include "Networking/Utility/Net_message.h"
#include <array>
#include <chrono>
#include <unordered_map>

struct Client_data
{
    uint32_t m_id = 0;
    std::array<float, 4> m_color = {0.0f, 0.0f, 0.0f, 0.0f};
    std::string m_name = "";
};

struct Server_message_data
{
    uint32_t m_sender_id = 0;
    std::string m_sender_name = "";
    std::array<float, 4> m_sender_color = {0.0f, 0.0f, 0.0f, 0.0f};
    std::string m_message = "";
    std::chrono::time_point<std::chrono::utc_clock> m_send_time;
};

struct Lobby_data
{
    std::vector<Client_data> m_clients;
};

class Net_message_converter
{
public:
    static Net::Net_message<Message_id> packade_server_lobby_information(
        const std::unordered_map<uint32_t, Client_data>& clients)
    {
        Net::Net_message<Message_id> net_message;
        net_message.set_id(Message_id::server_lobby_information);

        for (const auto& client : clients)
        {
            const Client_data& current = client.second;

            net_message.push_back_from_container(current.m_name.begin(), current.m_name.end());
            net_message << static_cast<uint64_t>(current.m_name.size());
            net_message << current.m_id;
            net_message << current.m_color;
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
            in_net_message >> current.m_color;
            in_net_message >> current.m_id;

            uint64_t name_size;
            in_net_message >> name_size;

            current.m_name = in_net_message.extract_as_string(name_size);
        }

        return output;
    }

    static Net::Net_message<Message_id> packade_server_client_left(const Client_data& client)
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::server_client_left);
        net_message.push_back_from_container(client.m_name.begin(), client.m_name.end());
        net_message << client.m_id;
        net_message << client.m_color;
        return net_message;
    }

    static Client_data extract_server_client_left(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_client_left)
            throw std::runtime_error("Wrong type of message");

        Client_data output;
        in_net_message >> output.m_color;
        in_net_message >> output.m_id;
        output.m_name = in_net_message.extract_as_string();
        return output;
    }

    static Net::Net_message<Message_id> packade_server_client_join(const Client_data& client)
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::server_client_join);
        net_message.push_back_from_container(client.m_name.begin(), client.m_name.end());
        net_message << client.m_id;
        net_message << client.m_color;
        return net_message;
    }

    static Client_data extract_server_client_join(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_client_join)
            throw std::runtime_error("Wrong type of message");

        Client_data output;
        in_net_message >> output.m_color;
        in_net_message >> output.m_id;
        output.m_name = in_net_message.extract_as_string();
        return output;
    }

    static Net::Net_message<Message_id> packade_client_information(
        std::string_view username, const std::array<float, 4> color)
    {
        Net::Net_message<Message_id> net_message;

        net_message.set_id(Message_id::client_information);
        net_message.push_back_from_container(username.begin(), username.end());
        net_message << color;
        return net_message;
    }

    static Client_data extract_client_information(Net::Net_message<Message_id>& in_net_message, uint32_t client_id)
    {
        if (in_net_message.get_id() != Message_id::client_information)
            throw std::runtime_error("Wrong type of message");

        Client_data output;
        output.m_id = client_id;
        in_net_message >> output.m_color;
        output.m_name = in_net_message.extract_as_string();
        return output;
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

    static Net::Net_message<Message_id> package_server_message(const Server_message_data& data)
    {
        Net::Net_message<Message_id> net_message;
        net_message.set_id(Message_id::server_message);
        net_message.push_back_from_container(data.m_message.begin(), data.m_message.end());
        net_message.push_back_from_container(data.m_sender_name.begin(), data.m_sender_name.end());
        net_message << static_cast<uint64_t>(data.m_sender_name.size());

        const std::string time_string = std::format("{0:%F}{0:%T}", data.m_send_time);
        net_message.push_back_from_container(time_string.begin(), time_string.end());
        net_message << static_cast<uint64_t>(time_string.size());

        net_message << data.m_sender_id;
        net_message << data.m_sender_color;
        return net_message;
    }

    static Server_message_data extract_server_message(Net::Net_message<Message_id>& in_net_message)
    {
        if (in_net_message.get_id() != Message_id::server_message)
            throw std::runtime_error("Wrong type of message");

        Server_message_data output;
        in_net_message >> output.m_sender_color;
        in_net_message >> output.m_sender_id;

        uint64_t time_string_size;
        in_net_message >> time_string_size;

        std::stringstream time_ss(in_net_message.extract_as_string(time_string_size));
        std::chrono::from_stream(time_ss, "%F%T", output.m_send_time);

        uint64_t sender_name__size;
        in_net_message >> sender_name__size;

        output.m_sender_name = in_net_message.extract_as_string(sender_name__size);
        output.m_message = in_net_message.extract_as_string();

        return output;
    }
};
