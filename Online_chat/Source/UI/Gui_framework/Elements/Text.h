#pragma once

#include "Element.h"

#include "ImGui/imgui.h"

namespace Gui
{
    enum class Text_type : uint8_t
    {
        default_type,
        colored,
        wrapped,
        disabled
    };

    class Text : public Element
    {
    public:
        Text(std::string_view name) : Element(name)
        {
        }

        void draw_element() override;
        void update() override;
        void set_text_type(Text_type new_type) noexcept;
        void set_text(std::string_view new_text) noexcept;
        void set_color(ImVec4 new_color) noexcept;

    private:
        Text_type m_type = Text_type::default_type;
        std::string m_text = "";
        ImVec4 m_color;
    };
} // namespace Gui
