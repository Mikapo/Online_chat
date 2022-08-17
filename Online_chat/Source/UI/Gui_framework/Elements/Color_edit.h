#pragma once

#include "Element.h"
#include <array>

namespace Gui
{
    class Color_edit : public Element
    {
    public:
        using Color_buffer_type = std::array<float, 4>;

        Color_edit(std::string_view name, int32_t order_id) : Element(name, order_id)
        {
        }

        void update() override;

        void add_flag(ImGuiColorEditFlags_ flag) noexcept;
        void set_color(const Color_buffer_type& new_color) noexcept;
        [[nodiscard]] const Color_buffer_type& get_color() const noexcept;

    private:
        void draw_element() override;

        Color_buffer_type m_color_buffer = {0.0f, 0.0f, 0.0f, 1.0f};
        ImGuiColorEditFlags m_flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_None;

        ADD_GUI_EVENT(on_change, Color_buffer_type, Color_buffer_type(), Color_buffer_type)
    };
} // namespace Gui
