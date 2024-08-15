#include "UICreation.h"
#include "utils.h"
#include <iostream>
#include <imgui.h>

void DrawMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Open"))
                {
                    std::cout << OpenFile() << "\n";
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
}