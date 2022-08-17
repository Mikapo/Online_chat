#pragma once

#include "Common.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

std::unordered_map<int32_t, ImFont*> Gui::Common::m_fonts;

void Gui::Common::initialize(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    m_fonts.emplace(0, io.Fonts->AddFontDefault());
}

void Gui::Common::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::Common::start_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::Common::end_frame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::Common::get_display_size(float& width, float& height)
{
    ImGuiIO& io = ImGui::GetIO();
    width = io.DisplaySize.x;
    height = io.DisplaySize.y;
}

ImFont* Gui::Common::get_font(int32_t index)
{
    return m_fonts.at(index);
}

ImFont* Gui::Common::add_font(std::string_view file_path, float font_pixels, int32_t id)
{
    auto& io = ImGui::GetIO();
    ImFont* new_font = io.Fonts->AddFontFromFileTTF(file_path.data(), font_pixels);
    m_fonts[id] = new_font;
    return new_font;
}
