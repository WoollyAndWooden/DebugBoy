#include "GameBoy.h"
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

GameBoy::GameBoy(std::string ROMName)
    : ROMName {ROMName}
{
    std::cout << "Initializing GameBoy emulator \n";

    // Load ROM into memory
    std::ifstream file(ROMName);

    if(!file)
    {
        throw std::exception("Failed to open ROM");
    }

    std::cout << "Loading " << ROMName << " ROM to memmory \n";

    char ch;
    while (file.get(ch))
    {
        ROM.push_back(ch);
    }

    file.close();
}