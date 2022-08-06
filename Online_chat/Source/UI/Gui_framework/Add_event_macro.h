#pragma once

#include <functional>
#include <optional>

#define ADD_GUI_EVENT(EVENT_NAME, EVENT_VALUE, DEFAULT_VALUE, ...)                                                     \
private:                                                                                                               \
    std::function<void(__VA_ARGS__)> m_##EVENT_NAME##_callback;                                                        \
    EVENT_VALUE EVENT_NAME##_since_last_check = DEFAULT_VALUE;                                                         \
                                                                                                                       \
public:                                                                                                                \
    template <typename Func_type>                                                                                      \
    void set_##EVENT_NAME##_callback(const Func_type& func)                                                            \
    {                                                                                                                  \
        m_##EVENT_NAME##_callback = func;                                                                              \
    }                                                                                                                  \
                                                                                                                       \
protected:                                                                                                             \
    template <typename... Argtypes>                                                                                    \
    bool broadcast_##EVENT_NAME##_if_changed(                                                                          \
        const EVENT_VALUE& event_value, std::optional<EVENT_VALUE> spesific_change = std::optional<EVENT_VALUE>(),     \
        Argtypes... args)                                                                                              \
    {                                                                                                                  \
        bool broadcasted = false;                                                                                      \
        if (event_value != EVENT_NAME##_since_last_check)                                                              \
        {                                                                                                              \
            if (m_##EVENT_NAME##_callback && (!spesific_change.has_value() || spesific_change.value() == event_value)) \
            {                                                                                                          \
                m_##EVENT_NAME##_callback(args...);                                                                    \
                broadcasted = true;                                                                                    \
            }                                                                                                          \
                                                                                                                       \
            EVENT_NAME##_since_last_check = event_value;                                                               \
        }                                                                                                              \
        return broadcasted;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
private:
