#pragma once

#include <unordered_map>

struct GLFWwindow;
struct ImFont;

namespace Gui
{
    class Common
    {
    public:
        Common() = delete;

        static void initialize(GLFWwindow* window);
        static void cleanup();
        static void start_frame();
        static void end_frame();
        static void get_display_size(float& width, float& height);
        static ImFont* get_font(int32_t id);
        static ImFont* add_font(std::string_view file_path, float font_pixels, int32_t id);

    private:
        static std::unordered_map<int32_t, ImFont*> m_fonts;
    };
} // namespace Gui
