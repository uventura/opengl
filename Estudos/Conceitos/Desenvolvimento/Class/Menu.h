#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Simple class to init some things from imgui
class Menu
{
public:
    Menu(GLFWwindow* window);
    ~Menu();

    // Between render and new frame put the imgui window.
    void newFrame();
    void render();
};