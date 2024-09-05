#pragma once
#include <string>
#include <memory>
#include "GameBoy.h"

// Used to control changes from Main Menu Bar
struct MainMenuBarChoice
{
    bool openFile {}; // Used to initialize new GB instance
    std::string filename;
    bool showRegistry {}; // This will be used to show current registry state
    bool showCurrentOpcode {}; // Open window with current opcode
};

void DrawMainMenuBar(MainMenuBarChoice * controls);
void HandleMainMenuBar(MainMenuBarChoice * controls, std::unique_ptr<GameBoy>& gb);

// Render instance specific windows
void RenderGBWindows(MainMenuBarChoice * controls, std::unique_ptr<GameBoy>& gb);