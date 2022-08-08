#include "Element.h"

void Gui::Element::draw()
{
    std::scoped_lock lock(m_mutex);

    for (const auto& color : m_colors)
        ImGui::PushStyleColor(color.first, color.second);

    bool did_push_width = false;
    if (m_width > 0)
    {
        ImGui::PushItemWidth(m_width);
        did_push_width = true;
    }

    ImGui::PushID(m_id);

    if (m_same_line)
        ImGui::SameLine(m_same_line_offset, m_same_line_spacing);

    draw_element();

    m_is_focused = ImGui::IsItemFocused();

    ImGui::PopStyleColor(m_colors.size());
    ImGui::PopID();

    if (did_push_width)
        ImGui::PopItemWidth();
}

void Gui::Element::set_width(float new_width)
{
    m_width = new_width;
}

void Gui::Element::add_color(ImGuiCol type, ImVec4 color)
{
    std::scoped_lock lock(m_mutex);

    m_colors[type] = color;
}

void Gui::Element::add_style(ImGuiStyleVar type, ImGuiStyle style)
{
    std::scoped_lock lock(m_mutex);

    m_styles[type] = style;
}

bool Gui::Element::is_focused() const noexcept
{
    return m_is_focused;
}

int32_t Gui::Element::get_order_id() const noexcept
{
    return m_order_id;
}

void Gui::Element::set_id(int32_t new_id) noexcept
{
    m_id = new_id;
}

void Gui::Element::set_on_same_line(bool enabled, float offset, float spacing) noexcept
{
    m_same_line = enabled;
    m_same_line_offset = offset;
    m_same_line_spacing = spacing;
}

std::string_view Gui::Element::get_name() const noexcept
{
    return m_name;
}
