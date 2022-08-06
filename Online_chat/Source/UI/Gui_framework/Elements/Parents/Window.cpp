#include "Window.h"

#include "ImGui/imgui.h"

void Gui::Window::draw_element()
{
    if (m_is_open)
    {
        ImGui::Begin(get_name().data(), &m_is_open, m_flags);
        m_changes.apply_changes();
        draw_children();
        ImGui::End();
    }
}

void Gui::Window::update()
{
    Parent::update();

    broadcast_on_closed_if_changed(m_is_open, false);
}

void Gui::Window::add_flag(ImGuiWindowFlags_ flag) noexcept
{
    m_flags |= flag;
}

void Gui::Window::set_window_size(float width, float height) noexcept
{
    m_changes.change_size({width, height});
}

void Gui::Window::set_window_pos(float x, float y) noexcept
{
    m_changes.change_pos({x, y});
}

void Gui::Window::set_scroll_y_ratio(float y) noexcept
{
    m_changes.set_scroll_pos(y);
}

bool Gui::Window::is_open() const noexcept
{
    return m_is_open;
}
