#pragma once

#include "Element.h"
#include "ImGui/imgui.h"

namespace Gui
{
    class Button : public Element
    {
    public:
        Button(std::string_view name) : Element(name)
        {
        }

        void draw_element() override;
        void update() override;
        void set_position(ImVec2 position) noexcept;

    private:
        ImVec2 m_position = {0.0f, 0.0f};
        bool m_pressed = false;

        ADD_GUI_EVENT(on_pressed, bool, false);
    };
} // namespace Gui
