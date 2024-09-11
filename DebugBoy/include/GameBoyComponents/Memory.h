#pragma once
#include <vector>
#include <array>
#include "consts.h"

class Memory
{
    // TODO: Implement mapper
    /*--------------------------------------------------------------------------------------
    Memory structure is as follows:
    0x0000 - 0x3FFF: 16KiB ROM bank #0 from cartridge
    0x4000 - 0x7FFF: 16KiB ROM bank #01-NN (Potentially switchable)
    0x8000 - 0x9FFF: 8KiB of Video RAM (VRAM) (Switchable in CGB mode)
    0xA000 - 0xBFFF: 8KiB External RAM (May be switchable. Not every cart has external RAM)
    0xC000 - 0xCFFF: 4KiB of Work RAM (WRAM)
    0xD000 = 0xDFFF: 4KiB of WRAM (Switchable banks 1-7 in CGB mode)
    0xE000 - 0xFDFF: Echo RAM of 0xC000 - 0xDDFF (Usage prohibited)
    0xFE00 - 0xFE9F: Object Attribute Memory (OAM)
    0xFEA0 - 0xFEFF: Usage prohibited
    0xFF00 - 0xFFFE: I/O Registers
    0xFF80 - 0xFFFE: High RAM (HRAM)
    0xFFFF = 0xFFFF: Interrupt Enable Register
    --------------------------------------------------------------------------------------*/

    // If needed, after every switchable range, there will be int to map which bank is currently used
    std::array<unsigned char, 0x4000> ROMBank0 {};

    std::vector<std::array<unsigned char, 0x4000>> ROMBanksSwitchable {};
    int ROMBanksSwitcher {};

    std::array<unsigned char, 0x2000> VRAM {};

    std::vector<std::array<unsigned char, 0x2000>> ERAM {};
    int ERAMSwitcher {};

    std::array<unsigned char, 0x1000> WRAM {};

    std::vector<std::array<unsigned char, 0x1000>> SwitchableWRAM {};
    int WRAMSwitcher {};

    // I'll leave Echo RAM for now, as it is just a copy with a prohibited use

    std::array<unsigned char, 0x009F> OAM {};

    // Apparently not usable, I'll leave it at that

    std::array<unsigned char, 0x007F> IO {};

    std::array<unsigned char, 0x007E> HRAM {};

    unsigned char IE {};

public:
    Memory() {}; // Won't compile without proper default constructor
    Memory(const std::vector<unsigned char> & ROM, bool CGB);  

    // We'll need the function to access memory from PC
      
};