#include "Window_changes.h"

void Window_changes::apply_changes()
{
    if (m_new_location.has_value())
    {
        ImGui::SetWindowPos(m_new_location.value());
        m_new_location.reset();
    }

    if (m_new_size.has_value())
    {
        ImGui::SetWindowSize(m_new_size.value());
        m_new_size.reset();
    }

    if (m_new_scroll_ratio.has_value())
    {
        ImGui::SetScrollHereY(m_new_scroll_ratio.value());
        m_new_scroll_ratio.reset();
    }
}

void Window_changes::change_pos(ImVec2 location) noexcept
{
    m_new_location = location;
}

void Window_changes::change_size(ImVec2 size) noexcept
{
    m_new_size = size;
}

void Window_changes::set_scroll_pos(float ratio) noexcept
{
    m_new_scroll_ratio = ratio;
}
