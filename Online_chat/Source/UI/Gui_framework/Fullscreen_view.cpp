#include "Fullscreen_view.h"
#include "Common.h"

Gui::Fullscreen_view::Fullscreen_view(std::string_view window_name)
{
    m_window = create_window(window_name);
    m_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration);
    m_window->add_flag(ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);
}

void Gui::Fullscreen_view::update()
{
    View::update();

    float width = 0.0f, height = 0.0f;
    Gui::get_display_size(width, height);

    m_window->set_window_size(width, height);
    m_window->set_window_pos(0, 0);
}

std::shared_ptr<Gui::Window> Gui::Fullscreen_view::get_fullscreen_window() const noexcept
{
    return m_window;
}
