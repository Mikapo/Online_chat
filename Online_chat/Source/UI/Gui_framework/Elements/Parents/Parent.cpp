#include "Parent.h"

void Gui::Parent::update()
{
    std::scoped_lock lock(m_update_mutex);

    for (auto& children : m_children)
        children.second->update();
}

void Gui::Parent::remove_child(int32_t order_id)
{
    std::scoped_lock lock(m_draw_mutex, m_update_mutex);
    m_children.erase(order_id);
}

void Gui::Parent::clear_children()
{
    std::scoped_lock lock(m_draw_mutex, m_update_mutex);
    m_children.clear();
}

void Gui::Parent::draw_children()
{
    std::scoped_lock lock(m_draw_mutex);

    for (auto& children : m_children)
        children.second->draw();
}
