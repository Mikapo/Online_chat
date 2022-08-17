#include "Color_edit.h"

void Gui::Color_edit::update()
{
    broadcast_on_change_if_changed(m_color_buffer, std::optional<Color_buffer_type>(), m_color_buffer);
}

void Gui::Color_edit::add_flag(ImGuiColorEditFlags_ flag) noexcept
{
    m_flags |= flag;
}

void Gui::Color_edit::set_color(const Color_buffer_type& new_color) noexcept
{
    m_color_buffer = new_color;
}

const Gui::Color_edit::Color_buffer_type& Gui::Color_edit::get_color() const noexcept
{
    return m_color_buffer;
}

void Gui::Color_edit::draw_element()
{
    ImGui::ColorEdit4(get_name().data(), m_color_buffer.data(), m_flags);
}
