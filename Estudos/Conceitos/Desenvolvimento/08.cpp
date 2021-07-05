#include "Class/HeaderProgram.h"

int main()
{
    Application window("Nova Interface de uso", 640, 480);
    Menu imgui(window.getWindowPtr());

    bool demo = true;
    while(window.Execute())
    {
        window.Clear();

        imgui.newFrame();
            ImGui::Begin("Janela Teste");
            ImGui::End();
        imgui.render();

        window.Update();
    }
}