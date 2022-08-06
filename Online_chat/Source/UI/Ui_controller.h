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
    void add_chat_message(std::string_view message, std::string_view sender);
    void add_chat_notification(std::string_view notification);

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
    Connect_view m_connect_view;
    Chat_view m_chat_view;

    Ui_state m_state = Ui_state::connect;
};
