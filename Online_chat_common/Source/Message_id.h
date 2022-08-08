#pragma once

#include <cstdint>

enum class Message_id : uint8_t
{
    client_set_name,
    client_message,
    server_message,
    server_client_join,
    server_client_left,
    server_lobby_information
};
