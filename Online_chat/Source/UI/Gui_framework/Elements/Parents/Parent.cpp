#include "Parent.h"

void Gui::Parent::update()
{
    std::scoped_lock lock(m_update_mutex);

    for (auto& children : m_children)
        children->update();
}

void Gui::Parent::draw_children()
{
    std::scoped_lock lock(m_draw_mutex);

    for (auto& children : m_children)
        children->draw();
}
