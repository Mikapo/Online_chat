#include "Chat_server.h"

int main()
{
    constexpr uint16_t port = 1234;
    Chat_server server(port);
    server.start();
}
