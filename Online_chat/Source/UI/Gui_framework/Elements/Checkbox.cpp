#include "Checkbox.h"

#include "ImGui/imgui.h"

void Gui::Checkbox::draw_element()
{
    ImGui::Checkbox(get_name().data(), &m_current);
}

void Gui::Checkbox::update()
{
    broadcast_on_change_if_changed(m_current, std::optional<bool>(), m_current);
}

void Gui::Checkbox::set_selected(bool selected) noexcept
{
    m_current = selected;
}
