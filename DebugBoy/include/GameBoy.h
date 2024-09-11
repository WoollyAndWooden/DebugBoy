#pragma once
#include <string>
#include <vector>
#include "CPU.h"
#include "Memory.h"
#include "utils.h"

class GameBoy
{
    // Cartridge Header checks
    bool logoPresent; // Checks if the logo, required by original bootloaders is present
    void checkIfLogo();

    // In some cases last 4 characters are manufacturer's code
    std::string title {};
    void readTitle();

    // Some Cartridges are monochrome only. Byte 0x0143 decides if game should launch in monochrome or color mode
    bool CGB;
    void checkCGB();

    // SGB will be ignored for now
    
    // Checking version of the ROM
    unsigned char version;
    void readVersion();

    // Verify Header checksum
    bool checksumCorrect;
    void verifyChecksum(); // Function taken from https://gbdev.io/pandocs/The_Cartridge_Header.html#014e-014f--global-checksum

    // ROM Needed to open game. Filename will also be needed to save games.
    std::string ROMName;

    // Actual ROM with instructions
    std::vector<unsigned char> ROM;

    // Initialize memory. Most of the components will have access to this.
    Memory memory;

    // Initialize neccessary components.
    CPU cpu{};

public:
    GameBoy(std::string ROMName);

    //Get Registry values from CPU
    registryParse getRegistry();
};