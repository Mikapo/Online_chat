#pragma once

#include "Element.h"
#include "ImGui/imgui.h"
#include <mutex>
#include <string>
#include <vector>

namespace Gui
{
    class Combo : public Element
    {
    public:
        Combo(std::string_view name, int32_t order_id = -1) : Element(name, order_id)
        {
        }

        void draw_element() override;
        void update() override;

        void change_selected(size_t new_selected);
        void add_flag(ImGuiComboFlags_ new_flag) noexcept;
        void set_options(const std::vector<std::string>& options) noexcept;
        void add_option(std::string_view new_option) noexcept;

    private:
        ImGuiComboFlags m_flags = ImGuiComboFlags_::ImGuiComboFlags_None;
        std::vector<std::string> m_options;
        size_t m_current_index = 0;
        std::mutex m_mutex;

        ADD_GUI_EVENT(on_changed, size_t, 0, std::string)
    };
} // namespace Gui
