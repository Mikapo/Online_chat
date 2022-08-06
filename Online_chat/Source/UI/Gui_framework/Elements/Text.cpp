#include "Text.h"

void Gui::Text::draw_element()
{
    switch (m_type)
    {
    case Text_type::default_type:
        ImGui::Text(m_text.data());
        break;
    case Text_type::colored:
        ImGui::TextColored(m_color, m_text.data());
        break;
    case Text_type::wrapped:
        ImGui::TextWrapped(m_text.data());
        break;
    case Text_type::disabled:
        ImGui::TextDisabled(m_text.data());
    }
}

void Gui::Text::update()
{
}

void Gui::Text::set_text_type(Text_type new_type) noexcept
{
    m_type = new_type;
}

void Gui::Text::set_text(std::string_view new_text) noexcept
{
    m_text = new_text;
}

void Gui::Text::set_color(ImVec4 new_color) noexcept
{
    m_color = new_color;
}
