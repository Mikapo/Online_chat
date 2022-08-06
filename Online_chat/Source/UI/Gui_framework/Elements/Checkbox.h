#pragma once

#include "Element.h"

namespace Gui
{
    class Checkbox : public Element
    {
    public:
        Checkbox(std::string_view name) : Element(name)
        {
        }

        void draw_element() override;
        void update() override;

        void set_selected(bool selected) noexcept;

    private:
        bool m_current = false;

        ADD_GUI_EVENT(on_change, bool, false, bool)
    };
} // namespace Gui
