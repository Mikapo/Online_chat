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
        Element(std::string_view name) : m_name(name)
        {
        }

        void draw();
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

        std::mutex m_mutex;
        int32_t m_id = 0;
        bool m_same_line = false;
        float m_same_line_offset = 0.0f, m_same_line_spacing = -1.0f;
        float m_width = -1;
        std::unordered_map<ImGuiCol, ImVec4> m_colors;
        std::unordered_map<ImGuiStyleVar, ImGuiStyle> m_styles;

        std::string m_name = "";
    };

    template <typename T>
    concept Element_concept = std::is_base_of_v<Element, T>;

} // namespace Gui
