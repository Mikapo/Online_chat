#pragma once

#include "../../Window_changes.h"
#include "ImGui/imgui.h"
#include "Parent.h"

namespace Gui
{
    class Window : public Parent
    {
    public:
        Window(std::string_view name, int32_t order_id = -1) : Parent(name, order_id)
        {
        }

        void draw_element() override;
        void update() override;

        void add_flag(ImGuiWindowFlags_ flag) noexcept;
        void set_window_size(float width, float height) noexcept;
        void set_window_pos(float x, float y) noexcept;
        void set_scroll_y_ratio(float y) noexcept;
        [[nodiscard]] bool is_open() const noexcept;

    private:
        bool m_is_open = true;
        ImGuiWindowFlags m_flags = ImGuiWindowFlags_::ImGuiWindowFlags_None;
        Window_changes m_changes;

        ADD_GUI_EVENT(on_closed, bool, true)
    };
} // namespace Gui
