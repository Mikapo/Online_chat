#include "Window.h"

#include "ImGui/imgui.h"

void Gui::Window::draw_element()
{
    if (m_is_open)
    {
        ImGui::Begin(get_name().data(), &m_is_open, m_flags);
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

void Gui::Window::set_window_size(float width, float height, ImGuiCond_ condition)
{
    ImGui::SetWindowSize(get_name().data(), {width, height}, condition);
}

void Gui::Window::set_window_pos(float x, float y, ImGuiCond_ condition)
{
    ImGui::SetWindowPos(get_name().data(), {x, y}, condition);
}

bool Gui::Window::is_open() const noexcept
{
    return m_is_open;
}
