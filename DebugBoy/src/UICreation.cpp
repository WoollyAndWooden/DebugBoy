#include "UICreation.h"
#include "utils.h"
#include <iostream>
#include <imgui.h>
#include <tinyfiledialogs.h>
#include <unordered_set>

void DrawMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Open"))
                {
                    char const * lFilterPatterns[2]={"*.gb", "*.gbc"};
                    std::string chosenFile = tinyfd_openFileDialog(NULL,
                                                NULL, 
                                                2, 
                                                lFilterPatterns, 
                                                "ROM file", 
                                                0);
                    std::cout << chosenFile << "\n";
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
}