#include "Slider.h"

void Gui::Slider::draw_element()
{
    switch (m_type)
    {
    case Gui::Slider_type::float_slider:
        ImGui::SliderFloat(get_name().data(), m_values.data(), m_min, m_max, m_format.data(), m_flags);
        break;
    case Gui::Slider_type::float2:
        ImGui::SliderFloat2(get_name().data(), m_values.data(), m_min, m_max, m_format.data(), m_flags);
        break;
    case Gui::Slider_type::float3:
        ImGui::SliderFloat3(get_name().data(), m_values.data(), m_min, m_max, m_format.data(), m_flags);
        break;
    case Gui::Slider_type::float4:
        ImGui::SliderFloat4(get_name().data(), m_values.data(), m_min, m_max, m_format.data(), m_flags);
        break;
    case Gui::Slider_type::angle:
        ImGui::SliderAngle(get_name().data(), m_values.data(), m_min, m_max, m_format.data(), m_flags);
        break;
    }
}

void Gui::Slider::update()
{
    broadcast_on_change_if_changed(m_values, std::optional<Event_type>(), m_values);
}

void Gui::Slider::set_value(float value, size_t index) noexcept
{
    m_values.at(index) = value;
}

void Gui::Slider::set_type(Slider_type new_type) noexcept
{
    m_type = new_type;
}

void Gui::Slider::set_limits(float new_min, float new_max) noexcept
{
    m_min = new_min;
    m_max = new_max;
}

void Gui::Slider::add_flag(ImGuiSliderFlags_ new_flag) noexcept
{
    m_flags |= new_flag;
}

void Gui::Slider::set_format(std::string_view new_format) noexcept
{
    m_format = new_format;
}
