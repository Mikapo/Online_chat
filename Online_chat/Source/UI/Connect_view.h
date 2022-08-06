#pragma once

#include "Gui_framework/Elements/Button.h"
#include "Gui_framework/Elements/Dummy.h"
#include "Gui_framework/Elements/Input_text.h"
#include "Gui_framework/Fullscreen_view.h"
#include <functional>
#include <memory>

class Connect_view : public Gui::Fullscreen_view
{
public:
    Connect_view();

    void update() override;

    template <typename Func_type>
    void set_on_connect_pressed(const Func_type& func)
    {
        m_on_connect_pressed = func;
    }

private:
    void correct_size();
    void on_connect_button_pressed();

    std::shared_ptr<Gui::Dummy> m_top_dummy = nullptr;
    std::shared_ptr<Gui::Input_text<30>> m_name_input = nullptr;
    std::shared_ptr<Gui::Input_text<14>> m_ip_input = nullptr;
    std::shared_ptr<Gui::Input_text<20>> m_port_input = nullptr;
    std::shared_ptr<Gui::Button> m_connect_button = nullptr;

    std::function<void(std::string_view, std::string_view, std::string_view)> m_on_connect_pressed;
};
