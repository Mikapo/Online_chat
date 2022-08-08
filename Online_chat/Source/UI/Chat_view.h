#pragma once

#include "Gui_framework/Elements/Button.h"
#include "Gui_framework/Elements/Input_text.h"
#include "Gui_framework/Elements/Parents/Child_window.h"
#include "Gui_framework/Elements/Parents/Window.h"
#include "Gui_framework/Elements/Text.h"
#include "Gui_framework/View.h"
#include <functional>

class Chat_view : public Gui::View
{
public:
    Chat_view();

    void correct_size();
    void update() override;
    void add_notification(std::string_view notification);
    void add_client_message(std::string_view message, std::string_view sender);
    void on_enter_pressed();
    void on_client_connect(std::string_view name, uint32_t id);
    void on_client_disconnect(std::string_view name, uint32_t id);
    void clear_chat();

    template <typename Func_name>
    void set_on_send_callback(const Func_name& func)
    {
        m_on_send = func;
    }

private:
    void create_windows();
    void on_send_button_pressed();

    std::shared_ptr<Gui::Window> m_chat_window = nullptr;
    std::shared_ptr<Gui::Window> m_input_window = nullptr;
    std::shared_ptr<Gui::Window> m_clients_window = nullptr;
    std::shared_ptr<Gui::Input_text<60>> m_chat_input = nullptr;
    std::shared_ptr<Gui::Button> m_send_button = nullptr;
    std::unordered_map<uint32_t, std::shared_ptr<Gui::Text>> m_client_texts;

    std::function<void(std::string_view)> m_on_send;
};
