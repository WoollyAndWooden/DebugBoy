#pragma once
#include <vector>

// original logo used to check validity of the cartridge
const std::vector<unsigned char> logoOG = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
                                         0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
                                         0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

// Define Cartridge type
enum CartType
{
    ROM_ONLY                       = 0x00,
    MBC1                           = 0x01,
    MBC1_RAM                       = 0x02,
    MBC1_RAM_BATTERY               = 0x03,
    MBC2                           = 0x0,
    MBC2_BATTERY                   = 0x06,
    ROM_RAM                        = 0x08,
    ROM_RAM_BATTERY                = 0x09,
    MMM01                          = 0x0B,
    MMM01_RAM                      = 0x0C,
    MMM01_RAM_BATTERY              = 0x0D,
    MBC3_TIMER_BATTERY             = 0x0F,
    MBC3_TIMER_RAM_BATTERY         = 0x10,
    MBC3                           = 0x11,
    MBC3_RAM                       = 0x12,
    MBC3_RAM_BATTERY               = 0x13,
    MBC5                           = 0x19,
    MBC5_RAM                       = 0x1A,
    MBC5_RAM_BATTERY               = 0x1B,
    MBC5_RUMBLE                    = 0x1C,
    MBC5_RUMBLE_RAM                = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY        = 0x1E,
    MBC6                           = 0x20,
    MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,
    POCKET_CAMERA                  = 0xFC,
    BANDAI_TAMAS                   = 0xFD,
    HuC3                           = 0xFE,
    HuC1_RAM_BATTERY               = 0xFF
};