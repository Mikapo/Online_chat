#include "Dummy.h"

void Gui::Dummy::draw_element()
{
    ImGui::Dummy(m_size);
}

void Gui::Dummy::update()
{
}

void Gui::Dummy::set_size(float width, float height) noexcept
{
    m_size = {width, height};
}
