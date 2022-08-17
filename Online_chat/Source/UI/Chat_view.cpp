#include "Chat_view.h"
#include "Color_themes.h"
#include "Gui_framework/Common.h"
#include "Gui_framework/Elements/Dummy.h"

Chat_view::Chat_view()
{
    create_windows();

    m_chat_input = m_input_window->add_children<Gui::Input_text<60>>("");
    m_chat_input->add_flag(ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue);

    m_send_button = m_input_window->add_children<Gui::Button>("Send");
    m_send_button->set_on_same_line(true);
    m_send_button->set_on_pressed_callback([this] { on_send_button_pressed(); });
}

void Chat_view::correct_size()
{
    float width = 0, height = 0;
    Gui::Common::get_display_size(width, height);

    constexpr float input_window_size = 55.0f;
    constexpr float client_window_size = 300.0f;

    m_chat_window->set_window_size(width - client_window_size, height - input_window_size);
    m_chat_window->set_window_pos(0.0f, 0.0f);

    m_input_window->set_window_size(width, input_window_size);
    m_input_window->set_window_pos(0, height - input_window_size);

    m_clients_window->set_window_size(client_window_size, height - input_window_size);
    m_clients_window->set_window_pos(width - client_window_size, 0.0f);
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

    m_clients_window = create_window("Clients");

    m_clients_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);
    m_clients_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration);
    m_clients_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoBringToFrontOnFocus);

    m_clients_window->add_color(ImGuiCol_::ImGuiCol_WindowBg, Color_themes::background);

    auto text = m_clients_window->add_children<Gui::Text>("Clients text");
    text->set_text("Clients:");
    text->set_font(1);

    auto clients_dummy = m_clients_window->add_children<Gui::Dummy>("Clients dummy");
    clients_dummy->set_size(1.0f, 5.0f);
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

void Chat_view::add_client_message(
    std::string_view message, std::string_view sender_name, const std::array<float, 4>& sender_color,
    uint32_t sender_id, std::string_view send_time)
{
    if (m_latest_sender_id != sender_id)
    {
        auto dummy = m_chat_window->add_children<Gui::Dummy>("Chat dummy");
        dummy->set_size(1.0f, 10.0f);

        auto sender_text = m_chat_window->add_children<Gui::Text>("Sender name");
        sender_text->set_text(sender_name);
        sender_text->add_color(
            ImGuiCol_::ImGuiCol_Text, {sender_color.at(0), sender_color.at(1), sender_color.at(2), sender_color.at(3)});
        sender_text->set_font(1);

        auto time_text = m_chat_window->add_children<Gui::Text>("Time");
        time_text->set_text(send_time);
        time_text->set_on_same_line(true, 0.0f, 10.0f);
        time_text->set_font(2);

        m_latest_sender_id = sender_id;
    }

    auto message_text = m_chat_window->add_children<Gui::Text>("Message");
    message_text->set_text(message);
    message_text->set_text_type(Gui::Text_type::wrapped);

    m_chat_window->set_scroll_y_ratio(1.0f);
}

void Chat_view::on_enter_pressed()
{
    if (m_chat_input->is_focused())
        on_send_button_pressed();
}

void Chat_view::on_client_connect(std::string_view name, const std::array<float, 4>& client_color, uint32_t id)
{
    auto client_text = m_clients_window->add_children<Gui::Text>(name);
    client_text->add_color(
        ImGuiCol_::ImGuiCol_Text, {client_color.at(0), client_color.at(1), client_color.at(2), client_color.at(3)});
    client_text->set_text(name);
    m_client_texts.emplace(id, client_text);
}

void Chat_view::on_client_disconnect(std::string_view name, const std::array<float, 4>& client_color, uint32_t id)
{
    auto client_text = m_client_texts.at(id);
    m_clients_window->remove_child(client_text->get_order_id());
    m_client_texts.erase(id);
}

void Chat_view::clear_chat()
{
    m_chat_window->clear_children();

    for (auto& client : m_client_texts)
        m_clients_window->remove_child(client.second->get_order_id());

    m_client_texts.clear();
}

void Chat_view::on_send_button_pressed()
{
    if (m_on_send && m_chat_input)
        m_on_send(m_chat_input->get_text());

    m_chat_input->clear();
    m_chat_input->focus();
}
