#include "Chat_view.h"
#include "Color_themes.h"
#include "Gui_framework/Common.h"
#include "Gui_framework/Elements/Text.h"

Chat_view::Chat_view() : Gui::Fullscreen_view("Chat_window")
{
    auto window = get_fullscreen_window();

    window->add_color(ImGuiCol_::ImGuiCol_WindowBg, Color_themes::background);
    window->add_color(ImGuiCol_::ImGuiCol_ChildBg, Color_themes::child_background);
    window->add_color(ImGuiCol_::ImGuiCol_FrameBg, Color_themes::text_frame);
    window->add_color(ImGuiCol_::ImGuiCol_Button, Color_themes::button);

    m_chat_window = window->add_children<Gui::Child_window>("Chat_window");
    m_chat_window->set_border(true);
    m_chat_window->set_flag(ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar);

    m_chat_input = window->add_children<Gui::Input_text<60>>("");
    m_send_button = window->add_children<Gui::Button>("Send");
    m_send_button->set_on_same_line(true);
    m_send_button->set_on_pressed_callback([this] { on_send_button_pressed(); });
}

void Chat_view::correct_size()
{
    float width = 0, height = 0;
    Gui::get_display_size(width, height);

    m_chat_window->set_size(width, height * 0.85f);
}

void Chat_view::update()
{
    Gui::Fullscreen_view::update();

    correct_size();
}

void Chat_view::add_notification(std::string_view notification)
{
    auto text = m_chat_window->add_children<Gui::Text>("Notification");
    text->set_text(notification);
}

void Chat_view::add_client_message(std::string_view message, std::string_view sender)
{
    const std::string formated_message = std::format("[{}] {}", sender, message);
    auto text = m_chat_window->add_children<Gui::Text>("Message");
    text->set_text(formated_message);
}

void Chat_view::on_send_button_pressed()
{
    if (m_on_send)
        m_on_send(m_chat_input->get_text());

    m_chat_input->clear();
}
