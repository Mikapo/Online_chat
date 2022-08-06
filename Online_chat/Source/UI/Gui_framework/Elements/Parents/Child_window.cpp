#include "Child_window.h"

void Gui::Child_window::draw_element()
{
    if (ImGui::BeginChild(get_name().data(), m_size, m_border, m_flags))
        draw_children();
    ImGui::EndChild();
}

void Gui::Child_window::set_size(float width, float height) noexcept
{
    m_size = {width, height};
}

void Gui::Child_window::set_border(bool border) noexcept
{
    m_border = border;
}

void Gui::Child_window::set_flag(ImGuiWindowFlags_ flag)
{
    m_flags |= flag;
}
