#include "Connect_view.h"
#include "Color_themes.h"
#include "Gui_framework/Common.h"

Connect_view::Connect_view() : Fullscreen_view("Connect_window")
{
    std::shared_ptr<Gui::Window> window = get_fullscreen_window();
    window->add_color(ImGuiCol_::ImGuiCol_WindowBg, Color_themes::background);
    window->add_color(ImGuiCol_::ImGuiCol_FrameBg, Color_themes::text_frame);
    window->add_color(ImGuiCol_::ImGuiCol_Button, Color_themes::button);

    m_top_dummy = window->add_children<Gui::Dummy>("Top dummy");

    window->add_children<Gui::Dummy>("Username_dummy");
    m_name_input = window->add_children<Gui::Input_text<30>>("Username");

    create_between_dummy(window);

    window->add_children<Gui::Dummy>("Color_dummy");
    m_color = window->add_children<Gui::Color_edit>("Color");

    create_between_dummy(window);

    window->add_children<Gui::Dummy>("Ip_dummy");
    m_ip_input = window->add_children<Gui::Input_text<30>>("IP");

    create_between_dummy(window);

    window->add_children<Gui::Dummy>("port_dummy");
    m_port_input = window->add_children<Gui::Input_text<20>>("Port");

    create_between_dummy(window);

    window->add_children<Gui::Dummy>("connect_dummy");
    m_connect_button = window->add_children<Gui::Button>("Connect");
    m_connect_button->set_on_pressed_callback([this] { on_connect_button_pressed(); });
}

void Connect_view::update()
{
    Gui::Fullscreen_view::update();

    correct_size();
}

void Connect_view::correct_size()
{
    float width = 0.0f, height = 0.0f;
    Gui::Common::get_display_size(width, height);

    m_top_dummy->set_size(0, height * 0.30f);

    resize_element(m_name_input);
    resize_element(m_color);
    resize_element(m_ip_input);
    resize_element(m_port_input);
    resize_element(m_connect_button);

    ImGui::GetIO().FontGlobalScale = 2.5f;
}

void Connect_view::on_connect_button_pressed()
{
    const std::string_view username = m_name_input->get_text();
    const std::array<float, 4>& color = m_color->get_color();
    const std::string_view ip = m_ip_input->get_text();
    const std::string_view port = m_port_input->get_text();

    if (m_on_connect_pressed)
        m_on_connect_pressed(username, color, ip, port);
}

void Connect_view::create_between_dummy(std::shared_ptr<Gui::Window> window)
{
    auto between_dummy = window->add_children<Gui::Dummy>("Between dummy");
    between_dummy->set_size(0.0f, 10.0f);
}

void Connect_view::resize_element(std::shared_ptr<Gui::Element> element)
{
    float width = 0.0f, height = 0.0f;
    Gui::Common::get_display_size(width, height);

    const float padding = width * 0.25f;
    const float size = width * 0.50f;

    element->set_on_same_line(true, padding);
    element->set_width(size);
}
