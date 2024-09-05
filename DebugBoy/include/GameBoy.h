#pragma once
#include <string>
#include <vector>
#include "CPU.h"

class GameBoy
{
    // ROM Needed to open game. Filename will also be needed to save games.
    std::string ROMName;

    // Actual ROM with instructions
    std::vector<char> ROM;

    // Initialize neccessary components.
    CPU CPU{};

public:
    GameBoy(std::string ROMName);
};