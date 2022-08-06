#pragma once

struct GLFWwindow;
namespace Gui
{
    void initialize(GLFWwindow* window);
    void cleanup();
    void start_frame();
    void end_frame();
    void get_display_size(float& width, float& height);
} // namespace Gui
