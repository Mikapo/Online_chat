#include "Button.h"

#include "ImGui/imgui.h"

void Gui::Button::draw_element()
{
    m_pressed = ImGui::Button(get_name().data(), m_position);
}

void Gui::Button::update()
{
    broadcast_on_pressed_if_changed(m_pressed, true);
}

void Gui::Button::set_position(ImVec2 position) noexcept
{
    m_position = position;
}
