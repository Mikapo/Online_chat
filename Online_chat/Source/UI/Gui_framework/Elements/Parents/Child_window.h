#pragma once

#include "ImGui/imgui.h"
#include "Parent.h"

namespace Gui
{
    class Child_window : public Parent
    {
    public:
        Child_window(std::string_view name) : Parent(name)
        {
        }

        void draw_element() override;
        void set_size(float width, float height) noexcept;
        void set_border(bool border) noexcept;
        void set_flag(ImGuiWindowFlags_ flag);

    private:
        ImGuiWindowFlags m_flags = ImGuiWindowFlags_::ImGuiWindowFlags_None;
        ImVec2 m_size = {0.0f, 0.0f};
        bool m_border = false;
    };
} // namespace Gui
