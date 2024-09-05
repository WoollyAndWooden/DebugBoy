#include "UICreation.h"
#include "utils.h"
#include "GameBoy.h"
#include <iostream>
#include <exception>
#include <memory>
#include <imgui.h>
#include <tinyfiledialogs.h>

void DrawMainMenuBar(MainMenuBarChoice * controls)
{
    if (ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Open"))
                {
                    char const * lFilterPatterns[2]={"*.gb", "*.gbc"};
                    controls->openFile = 1;
                    controls->filename = tinyfd_openFileDialog(NULL,
                                                NULL, 
                                                2, 
                                                lFilterPatterns, 
                                                "ROM file", 
                                                0);
                }
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("Displayed Windows"))
            {
                ImGui::MenuItem("Registry", NULL, &controls->showRegistry);
                ImGui::MenuItem("Opcodes", NULL, &controls->showCurrentOpcode);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
}

void HandleMainMenuBar(MainMenuBarChoice * controls, std::unique_ptr<GameBoy>& gb)
{
    if(controls->openFile)
    {
        try
        {
            gb = std::make_unique<GameBoy>(controls->filename);
        }
        catch (const std::exception &e)
        {

            ImGui::Begin("Error");
            ImGui::Text(e.what());
            ImGui::End();
        }
        controls->openFile = !controls->openFile;
    }
    if(gb)
        RenderGBWindows(controls, gb);
}

void RenderGBWindows(MainMenuBarChoice * controls, std::unique_ptr<GameBoy>& gb)
{
    if(controls->showRegistry)
    {
        ImGui::Begin("Registry", &controls->showRegistry);
        ImGui::Text("Registries will be displayed here");
        ImGui::End();
    }
    if(controls->showCurrentOpcode)
    {
        ImGui::Begin("Opcodes", &controls->showCurrentOpcode);
        ImGui::Text("Opcodes will be displayed here");
        ImGui::End();
    }
}