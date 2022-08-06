#include "View.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

void Gui::View::draw()
{
    std::scoped_lock lock(m_draw_mutex);

    for (auto& window : m_windows)
        window->draw();
}

void Gui::View::update()
{
    std::scoped_lock lock(m_update_mutex);

    for (auto& window : m_windows)
        window->update();
}

std::shared_ptr<Gui::Window> Gui::View::create_window(std::string_view name)
{
    std::scoped_lock lock(m_draw_mutex, m_update_mutex);

    std::shared_ptr new_window = std::make_shared<Window>(name);
    m_windows.push_back(new_window);
    return new_window;
}
