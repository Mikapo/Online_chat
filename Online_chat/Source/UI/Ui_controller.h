#pragma once

#include "Chat_view.h"
#include "Connect_view.h"

enum class Ui_state : uint8_t
{
    connect,
    chat
};

struct GLFWwindow;
class Ui_controller
{
public:
    void init(GLFWwindow* window);
    void draw();
    void update();
    void set_state(Ui_state new_state);
    void add_chat_message(
        std::string_view message, std::string_view sender_name, const std::array<float, 4>& sender_color,
        uint32_t sender_id, std::string_view send_time);
    void add_chat_notification(std::string_view notification);
    void on_enter_pressed();
    void on_client_connect(std::string_view name, const std::array<float, 4>& client_color, uint32_t id);
    void on_client_disconnect(std::string_view name, const std::array<float, 4>& client_color, uint32_t id);
    void clear_chat();

    template <typename Func_type>
    void set_on_connect_callback(const Func_type& func)
    {
        m_connect_view.set_on_connect_pressed(func);
    }

    template <typename Func_type>
    void set_on_send_callback(const Func_type& func)
    {
        m_chat_view.set_on_send_callback(func);
    }

private:
    void setup_fonts();

    Connect_view m_connect_view;
    Chat_view m_chat_view;

    Ui_state m_state = Ui_state::connect;
};
