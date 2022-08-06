#pragma once

#include <deque>
#include <mutex>

namespace Net
{
    template <typename T>
    class Thread_safe_deque
    {
    public:
        Thread_safe_deque() = default;
        Thread_safe_deque(const Thread_safe_deque&) = delete;
        Thread_safe_deque(Thread_safe_deque&&) = delete;
        ~Thread_safe_deque()
        {
            clear();
        }

        Thread_safe_deque& operator=(const Thread_safe_deque&) = delete;
        Thread_safe_deque& operator=(Thread_safe_deque&&) = delete;

        [[nodiscard]] const T& front()
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.front();
        }

        [[nodiscard]] const T& back()
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.back();
        }

        void push_front(const T& item)
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.push_front(std::move(item));
        }

        void push_back(const T& item)
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.push_back(std::move(item));
        }

        [[nodiscard]] bool empty()
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.empty();
        }

        template <typename... Argtypes>
        void erase(const Argtypes&... args)
        {
            std::scoped_lock lock(m_mutex);
            m_queue.erase(args...);
        }

        [[nodiscard]] size_t count()
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.count();
        }

        void clear()
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.clear();
        }

        T pop_front()
        {
            std::scoped_lock lock(m_mutex);
            auto temp = std::move(m_queue.front());
            m_queue.pop_front();
            return temp;
        }

        T pop_back()
        {
            std::scoped_lock lock(m_mutex);
            auto temp = std::move(m_queue.back());
            m_queue.pop_back();
            return temp;
        }

    private:
        std::mutex m_mutex;
        std::deque<T> m_queue;
    };
} // namespace Net
