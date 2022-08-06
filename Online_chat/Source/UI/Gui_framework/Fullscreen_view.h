#pragma once

#include "View.h"

namespace Gui
{
    class Fullscreen_view : public View
    {
    public:
        Fullscreen_view(std::string_view window_name);

        void update() override;
        [[nodiscard]] std::shared_ptr<Window> get_fullscreen_window() const noexcept;

    private:
        std::shared_ptr<Window> m_window;
    };
} // namespace Gui
