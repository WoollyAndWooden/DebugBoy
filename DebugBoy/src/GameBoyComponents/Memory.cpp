#include "Memory.h"
#include "consts.h"
#include <vector>
#include <algorithm>
#include <exception>
#include <iostream>

Memory::Memory(const std::vector<unsigned char> & ROM, bool CGB)
{
    // First check what Cartridge type is being used here
    switch(ROM[0x0147]) // This byte represents the type of cart
    {
        case CartType::ROM_ONLY: // No additional memory bank is in this cartridge, 32KiB total
        {
            // Bank #1 needs to be initialized
            ROMBanksSwitchable.push_back({});
            std::cout << ROMBanksSwitchable[0][0x05F0];
            
            std::copy(ROM.begin(), ROM.begin() + 0x3FFF, ROMBank0.begin()); // 16KiB of ROM goes to bank #0
            std::copy(ROM.begin() + 0x4000, ROM.end(), ROMBanksSwitchable[0].begin()); // And 16KiB goes to bank #1
            break;
        }
        default:
        {
            throw std::exception("Cart type not yet implemented or invalid");
        }
    }

    // initialize switchable VRAM and WRAM if CGB mode
    if(CGB)
    {
        for(int i = 0; i < 7; i++)
        {
            SwitchableWRAM.push_back({});
        }
    }
}