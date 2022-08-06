#pragma once

#include "ImGui/imgui.h"
#include "Parent.h"

namespace Gui
{
    class Window : public Parent
    {
    public:
        Window(std::string_view name) : Parent(name)
        {
        }

        void draw_element() override;
        void update() override;

        void add_flag(ImGuiWindowFlags_ flag) noexcept;
        void set_window_size(float width, float height, ImGuiCond_ condition = ImGuiCond_::ImGuiCond_None);
        void set_window_pos(float x, float y, ImGuiCond_ condition = ImGuiCond_::ImGuiCond_None);
        [[nodiscard]] bool is_open() const noexcept;

    private:
        bool m_is_open = true;
        ImGuiWindowFlags m_flags = ImGuiWindowFlags_::ImGuiWindowFlags_None;

        ADD_GUI_EVENT(on_closed, bool, true)
    };
} // namespace Gui
