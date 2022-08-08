#pragma once

#include "Element.h"
#include "ImGui/imgui.h"
#include <array>
#include <deque>
#include <mutex>

namespace Gui
{
    constexpr size_t INPUT_TEXT_DEFAULT_BUFFER_SIZE = 30;

    template <size_t buffer_size = INPUT_TEXT_DEFAULT_BUFFER_SIZE>
    class Input_text : public Element
    {
    public:
        Input_text(std::string_view name, int32_t order_id) : Element(name, order_id)
        {
            clear();
        }

        void update() override
        {
            std::scoped_lock lock(m_mutex);

            if (broadcast_on_changed_if_changed(m_edited, true, m_buffer.data()))
                m_edited = false;
        }

        [[nodiscard]] const char* get_text() const noexcept
        {
            return m_buffer.data();
        }

        void add_flag(ImGuiInputTextFlags_ flag) noexcept
        {
            m_flags |= flag;
        }

        void focus() noexcept
        {
            m_focus = true;
        }

        void clear() noexcept
        {
            m_clear = true;
        }

    private:
        void draw_element() override
        {
            std::scoped_lock lock(m_mutex);

            if (m_focus && !m_clear)
            {
                ImGui::SetKeyboardFocusHere();
                m_focus = false;
            }

            if (ImGui::InputText(get_name().data(), m_buffer.data(), m_buffer.size()), m_flags)
                m_edited = true;

            if (m_clear)
            {
                m_buffer.fill(0);
                m_clear = false;
            }
        }

        bool m_edited = false;
        ImGuiInputTextFlags m_flags = ImGuiInputTextFlags_::ImGuiInputTextFlags_None;
        std::array<char, buffer_size> m_buffer;
        std::mutex m_mutex;
        bool m_clear = false;
        bool m_focus;

        ADD_GUI_EVENT(on_changed, bool, false, const char*)
    };
} // namespace Gui
