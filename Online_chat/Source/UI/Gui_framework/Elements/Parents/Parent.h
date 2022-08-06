#pragma once

#include "../Element.h"
#include <memory>
#include <thread>
#include <mutex>

namespace Gui
{
    class Parent : public Element
    {
    public:
        Parent(std::string_view name) : Element(name)
        {
        }

        void update() override;

        template <Element_concept T>
        std::shared_ptr<T> add_children(std::string_view name)
        {
            std::scoped_lock lock(m_draw_mutex, m_update_mutex);

            std::shared_ptr<T> new_children = std::make_shared<T>(name);
            m_children.push_back(new_children);
            return new_children;
        }

    protected:
        void draw_children();

    private:
        std::vector<std::shared_ptr<Element>> m_children;
        std::mutex m_draw_mutex;
        std::mutex m_update_mutex;
    };
} // namespace Gui
