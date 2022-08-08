#pragma once

#include "Element.h"
#include "ImGui/imgui.h"
#include <array>

namespace Gui
{
    enum class Slider_type : uint8_t
    {
        float_slider,
        float2,
        float3,
        float4,
        angle
    };

    class Slider : public Element
    {
    public:
        Slider(std::string_view name, int32_t order_id = -1) : Element(name, order_id)
        {
        }

        void draw_element() override;
        void update() override;
        void set_value(float value, size_t index = 0) noexcept;
        void set_type(Slider_type new_type) noexcept;
        void set_limits(float new_min, float new_max) noexcept;
        void add_flag(ImGuiSliderFlags_ new_flag) noexcept;
        void set_format(std::string_view new_format) noexcept;

    private:
        std::array<float, 4> m_values = {0.0f, 0.0f, 0.0f, 0.0f};
        Slider_type m_type = Slider_type::float_slider;
        float m_max = 100.0f, m_min = 0.0f;
        ImGuiSliderFlags m_flags = ImGuiSliderFlags_::ImGuiSliderFlags_None;
        std::string m_format = "%.f";

        using Event_type = std::array<float, 4>;
        ADD_GUI_EVENT(on_change, Event_type, Event_type(), const Event_type&)
    };
} // namespace Gui
