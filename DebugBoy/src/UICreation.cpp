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
         // Using those as a base value to create width/height that are factor of the size of our font
        const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        RenderGBRegistry(gb->getRegistry());
        ImGui::End();
    }
    if(controls->showCurrentOpcode)
    {
        ImGui::Begin("Opcodes", &controls->showCurrentOpcode);
        ImGui::Text("Opcodes will be displayed here");
        ImGui::End();
    }
}

void RenderGBRegistry(registryParse parse)
{
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders;
    ImGui::BeginTable("Current state of the registers", 3, flags);
    ImGui::TableSetupColumn("16-bit registry");
    ImGui::TableSetupColumn("High");
    ImGui::TableSetupColumn("Low");
    ImGui::TableHeadersRow();

    // First row: one char and a nested table of Flags
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("AF");

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.A);
    
    // Nested table for Flags.
    ImGui::TableNextColumn();
        ImGui::BeginTable("Flags", 4, flags);
        ImGui::TableSetupColumn("Zero Flag");
        ImGui::TableSetupColumn("Substraction Flag");
        ImGui::TableSetupColumn("Half Carry Flag");
        ImGui::TableSetupColumn("Carry Flag");
        ImGui::TableHeadersRow();
        
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("%d", parse.z);
        ImGui::TableNextColumn();
        ImGui::Text("%d", parse.n);
        ImGui::TableNextColumn();
        ImGui::Text("%d", parse.h);
        ImGui::TableNextColumn();
        ImGui::Text("%d", parse.c);
    ImGui::EndTable();

    // Up to SP and PC it's simpler
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("BC");

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.B);

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.C);


    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("DE");

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.D);

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.E);


    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("DE");

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.H);

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.L);


    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("SP");

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.SP);


    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("PC");

    ImGui::TableNextColumn();
    ImGui::Text("%x", parse.PC);

    ImGui::EndTable();
}