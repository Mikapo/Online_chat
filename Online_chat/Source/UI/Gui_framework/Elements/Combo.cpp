#include "Combo.h"

void Gui::Combo::draw_element()
{
    std::scoped_lock lock(m_mutex);

    if (m_options.empty())
        return;

    if (ImGui::BeginCombo(get_name().data(), m_options.at(m_current_index).data(), m_flags))
    {
        for (size_t i = 0; i < m_options.size(); ++i)
        {
            const bool is_selected = i == m_current_index;

            if (ImGui::Selectable(m_options.at(i).data(), is_selected))
                m_current_index = i;

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }
}

void Gui::Combo::update()
{
    broadcast_on_changed_if_changed(m_current_index, std::optional<size_t>(), m_options.at(m_current_index));
}

void Gui::Combo::change_selected(size_t new_selected)
{
    std::scoped_lock lock(m_mutex);

    if (new_selected < 0 || new_selected > m_options.size() - 1)
        throw std::out_of_range("Selection is out of range");

    m_current_index = new_selected;
}

void Gui::Combo::add_flag(ImGuiComboFlags_ new_flag) noexcept
{
    m_flags |= new_flag;
}

void Gui::Combo::set_options(const std::vector<std::string>& options) noexcept
{
    if (options.empty())
        return;

    std::scoped_lock lock(m_mutex);
    m_options = options;
}

void Gui::Combo::add_option(std::string_view new_option) noexcept
{
    std::scoped_lock lock(m_mutex);
    m_options.emplace_back(new_option);
}
