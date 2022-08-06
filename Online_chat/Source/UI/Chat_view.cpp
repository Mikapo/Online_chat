#include "Chat_view.h"
#include "Color_themes.h"
#include "Gui_framework/Common.h"
#include "Gui_framework/Elements/Text.h"

Chat_view::Chat_view()
{
    create_windows();

    m_chat_input = m_input_window->add_children<Gui::Input_text<60>>("");
    m_send_button = m_input_window->add_children<Gui::Button>("Send");
    m_send_button->set_on_same_line(true);
    m_send_button->set_on_pressed_callback([this] { on_send_button_pressed(); });
}

void Chat_view::correct_size()
{
    float width = 0, height = 0;
    Gui::get_display_size(width, height);

    m_chat_window->set_window_size(width, height * 0.9f);
    m_chat_window->set_window_pos(0.0f, 0.0f);

    m_input_window->set_window_size(width, height * 0.1f);
    m_input_window->set_window_pos(0, height * 0.9f);
}

void Chat_view::create_windows()
{

    m_chat_window = create_window("chat_window");

    m_chat_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar);
    m_chat_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);
    m_chat_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration);
    m_chat_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus);

    m_chat_window->add_color(ImGuiCol_::ImGuiCol_WindowBg, Color_themes::chat_background);

    m_input_window = create_window("Input");

    m_input_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);
    m_input_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration);
    m_input_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus);

    m_input_window->add_color(ImGuiCol_::ImGuiCol_WindowBg, Color_themes::background);
    m_input_window->add_color(ImGuiCol_::ImGuiCol_FrameBg, Color_themes::text_frame);
    m_input_window->add_color(ImGuiCol_::ImGuiCol_Button, Color_themes::button);
}

void Chat_view::update()
{
    Gui::View::update();

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
    m_chat_window->set_scroll_y_ratio(-1.0f);
}

void Chat_view::on_send_button_pressed()
{
    if (m_on_send)
        m_on_send(m_chat_input->get_text());

    m_chat_input->clear();
}
