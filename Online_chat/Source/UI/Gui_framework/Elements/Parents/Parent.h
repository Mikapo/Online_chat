#pragma once

#include "../Element.h"
#include <map>
#include <memory>
#include <thread>

namespace Gui
{
    class Parent : public Element
    {
    public:
        Parent(std::string_view name, int32_t order_id = -1) : Element(name, order_id)
        {
        }

        void update() override;

        template <Element_concept T>
        std::shared_ptr<T> add_children(std::string_view name)
        {
            std::scoped_lock lock(m_draw_mutex, m_update_mutex);

            std::shared_ptr<T> new_children = std::make_shared<T>(name, ++m_order_counter);
            m_children.emplace(m_order_counter, new_children);
            return new_children;
        }

        void remove_child(int32_t order_id);
        void clear_children();

    protected:
        void draw_children();

    private:
        std::map<int32_t, std::shared_ptr<Element>> m_children;
        int32_t m_order_counter = 0;

        std::mutex m_draw_mutex;
        std::mutex m_update_mutex;
    };
} // namespace Gui
