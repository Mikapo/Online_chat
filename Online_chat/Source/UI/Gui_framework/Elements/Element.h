#pragma once

#include "../Add_event_macro.h"
#include "ImGui/imgui.h"
#include <mutex>
#include <string>
#include <type_traits>

namespace Gui
{
    class Element
    {
    public:
        Element(std::string_view name, int32_t order_id = -1) : m_name(name), m_order_id(order_id)
        {
        }

        void draw();

        [[nodiscard]] bool is_focused() const noexcept;
        [[nodiscard]] int32_t get_order_id() const noexcept;
        void set_id(int32_t new_id) noexcept;
        void set_on_same_line(bool enabled, float offset = 0.0f, float spacing = -0.0f) noexcept;
        void set_width(float new_width);
        void add_color(ImGuiCol type, ImVec4 color);
        void add_style(ImGuiStyleVar type, ImGuiStyle style);
        virtual void update() = 0;

    protected:
        [[nodiscard]] std::string_view get_name() const noexcept;

    private:
        virtual void draw_element() = 0;

        std::string m_name = "";
        int32_t m_id = 0;
        int32_t m_order_id = -1;
        bool m_same_line = false;
        float m_same_line_offset = 0.0f, m_same_line_spacing = -1.0f;
        float m_width = -1;

        std::unordered_map<ImGuiCol, ImVec4> m_colors;
        std::unordered_map<ImGuiStyleVar, ImGuiStyle> m_styles;

        bool m_is_focused = false;

        std::mutex m_mutex;
    };

    template <typename T>
    concept Element_concept = std::is_base_of_v<Element, T>;

} // namespace Gui
