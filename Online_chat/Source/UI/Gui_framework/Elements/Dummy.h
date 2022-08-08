#pragma once

#include "Element.h"

#include "ImGui/imgui.h"

namespace Gui
{
    class Dummy : public Element
    {
    public:
        Dummy(std::string_view name, int32_t order_id = -1) : Element(name, order_id)
        {
        }

        void draw_element() override;
        void update() override;

        void set_size(float width, float height) noexcept;

    private:
        ImVec2 m_size = {0.0f, 0.0f};
    };
} // namespace Gui
