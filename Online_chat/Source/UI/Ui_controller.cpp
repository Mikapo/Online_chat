#include "Ui_controller.h"
#include "Gui_framework/Gui_framework.h"

void Ui_controller::init(GLFWwindow* window)
{
    Gui::initialize(window);
}

void Ui_controller::draw()
{
    Gui::start_frame();

    switch (m_state)
    {
    case Ui_state::connect:
        m_connect_view.draw();
        break;
    case Ui_state::chat:
        m_chat_view.draw();
        break;
    default:
        break;
    }
    Gui::end_frame();
}

void Ui_controller::update()
{
    switch (m_state)
    {
    case Ui_state::connect:
        m_connect_view.update();
        break;
    case Ui_state::chat:
        m_chat_view.update();
        break;
    }
}

void Ui_controller::set_state(Ui_state new_state)
{
    m_state = new_state;
}

void Ui_controller::add_chat_message(std::string_view message, std::string_view sender)
{
    m_chat_view.add_client_message(message, sender);
}

void Ui_controller::add_chat_notification(std::string_view notification)
{
    m_chat_view.add_notification(notification);
}

void Ui_controller::on_enter_pressed()
{
    if (m_state == Ui_state::chat)
        m_chat_view.on_enter_pressed();
}

void Ui_controller::on_client_connect(std::string_view name, uint32_t id)
{
    m_chat_view.on_client_connect(name, id);
}

void Ui_controller::on_client_disconnect(std::string_view name, uint32_t id)
{
    m_chat_view.on_client_disconnect(name, id);
}

void Ui_controller::clear_chat()
{
    m_chat_view.clear_chat();
}
