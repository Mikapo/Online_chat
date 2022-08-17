#include "Chat_client.h"
#include "Net_message_converter.h"
#include <chrono>

Chat_client::Chat_client()
{
    add_accepted_message(Message_id::server_message);
    add_accepted_message(Message_id::server_client_join);
    add_accepted_message(Message_id::server_client_left);
    add_accepted_message(Message_id::server_lobby_information);
}

void Chat_client::start()
{
    setup_callbacks();
    m_application.set_window_dimensions(800, 800);
    m_application.start();
}

void Chat_client::setup_callbacks()
{
    m_application.set_render_callback(this, &Chat_client::render);
    m_application.set_on_window_open_callback(this, &Chat_client::on_window_open);
    m_application.set_on_key_event_callback(this, &Chat_client::on_input);
    m_application.set_cleanup_callback(this, &Chat_client::cleanup);

    m_ui_controller.set_on_connect_callback([this](
                                                std::string_view username, const std::array<float, 4>& color,
                                                std::string_view ip,
                                                std::string_view port) { on_connect(username, color, ip, port); });

    m_ui_controller.set_on_send_callback([this](std::string_view message) { on_send_message(message); });
}

void Chat_client::on_window_open()
{
    m_ui_controller.init(m_application.get_window());

    m_logic_thread_stop_flag = false;
    m_logic_thread = std::thread([this] { logic_thread(); });
}

void Chat_client::render()
{
    m_ui_controller.draw();
}

void Chat_client::logic_thread()
{
    while (!m_logic_thread_stop_flag)
    {
        m_ui_controller.update();

        if (is_connected())
        {
            if (!m_has_send_information)
                send_client_information();

            update();
            m_ui_controller.set_state(Ui_state::chat);
        }
        else
            m_ui_controller.set_state(Ui_state::connect);
    }
}

void Chat_client::cleanup()
{
    m_logic_thread_stop_flag = true;
    m_logic_thread.join();
}

void Chat_client::on_connect(
    std::string_view username, const std::array<float, 4>& color, std::string_view ip, std::string_view port)
{
    m_ui_controller.clear_chat();
    m_username = username;
    m_color = color;
    m_has_send_information = false;
    connect(ip, port);
}

void Chat_client::send_client_information()
{
    auto net_message = Net_message_converter::packade_client_information(m_username, m_color);
    send_message(net_message);
    m_has_send_information = true;
}

void Chat_client::on_input(Input_key key, Input_action action)
{
    if (key == Input_key::enter && action == Input_action::press)
        m_ui_controller.on_enter_pressed();
}

void Chat_client::on_send_message(std::string_view message)
{
    if (message.empty())
        return;

    auto net_message = Net_message_converter::package_client_message(message);
    send_message(net_message);
}

void Chat_client::handle_lobby_information(const Lobby_data& lobby_data)
{
    for (auto client : lobby_data.m_clients)
        m_ui_controller.on_client_connect(client.m_name, client.m_color, client.m_id);
}

void Chat_client::handle_message(const Server_message_data& message)
{
    const auto time_zone = std::chrono::current_zone();
    const std::chrono::utc_clock clock;
    const std::chrono::zoned_time current_time = {time_zone, clock.to_sys(message.m_send_time)};

    const std::string time_string = std::format("{0:%R}", current_time);

    m_ui_controller.add_chat_message(
        message.m_message, message.m_sender_name, message.m_sender_color, message.m_sender_id, time_string);
};

void Chat_client::on_message(Net::Net_message<Message_id> net_message)
{
    switch (net_message.get_id())
    {
    case Message_id::server_message: {
        const auto message_data = Net_message_converter::extract_server_message(net_message);
        handle_message(message_data);
        break;
    }

    case Message_id::server_client_join: {
        const auto client_data = Net_message_converter::extract_server_client_join(net_message);
        m_ui_controller.on_client_connect(client_data.m_name, client_data.m_color, client_data.m_id);
        break;
    }

    case Message_id::server_client_left: {
        const auto client_data = Net_message_converter::extract_server_client_left(net_message);
        m_ui_controller.on_client_disconnect(client_data.m_name, client_data.m_color, client_data.m_id);
        break;
    }

    case Message_id::server_lobby_information: {
        const auto lobby_data = Net_message_converter::extract_server_lobby_information(net_message);
        handle_lobby_information(lobby_data);
        break;
    }

    default:
        disconnect();
        break;
    }
}
