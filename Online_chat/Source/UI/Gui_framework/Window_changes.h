#pragma once

#include "ImGui/imgui.h"
#include <optional>

class Window_changes
{
public:
    void apply_changes();
    void change_pos(ImVec2 position) noexcept;
    void change_size(ImVec2 size) noexcept;
    void set_scroll_pos(float position) noexcept;

private:
    std::optional<ImVec2> m_new_location;
    std::optional<ImVec2> m_new_size;
    std::optional<float> m_new_scroll_ratio;
};
