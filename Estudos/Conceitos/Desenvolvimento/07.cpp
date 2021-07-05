#include "Class/HeaderProgram.h"

#include "Class/imgui/imgui.h"
#include "Class/imgui/imgui_impl_glfw.h"
#include "Class/imgui/imgui_impl_opengl3.h"

int main()
{
    Application window("Utilizando ImGUI...", 640, 480, true);

    const char* glsl_version = "#version 130";

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindowPtr(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Execution
    while(window.Execute())
    {
        io.WantCaptureMouse;
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&show_another_window);
        ImGui::Render();

        window.Update();
        window.Clear();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}