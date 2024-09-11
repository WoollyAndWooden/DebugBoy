#include "GameBoy.h"
#include "utils.h"
#include "consts.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <exception> 

GameBoy::GameBoy(std::string ROMName)
    : ROMName {ROMName}
{
    // Load ROM into memory
    std::ifstream file(ROMName, std::ios::binary);

    if(!file)
    {
        throw std::exception("Failed to open ROM");
    }

    // Read the data byte by byte
    unsigned char ch;

    ROM.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());


    file.close();

    // It'll read certain sections of Cartridge Header.
    checkIfLogo();
    if(!logoPresent)
        std::cout << "not ";
    std::cout << "legit\n";

    readTitle();
    std::cout << title << std::endl;

    checkCGB();
    if(CGB)
        std::cout << "GBC enabled game\n";
    else
        std::cout << "Monochrome game\n";

    readVersion();

    verifyChecksum();
    std::cout << "Checksum verified ";
    if(!checksumCorrect)
        std::cout << "in";
    std::cout << "correctly\n";

    // Initializing memory
    //try
    //{
        memory = Memory(ROM, CGB);
    //}
    //catch(std::exception &e)
    //{

    //}

}

registryParse GameBoy::getRegistry()
{
    registryParse parse;
    parse.A = cpu.getA();
    parse.z = cpu.get_z();
    parse.n = cpu.get_n();
    parse.h = cpu.get_h();
    parse.c = cpu.get_c();

    parse.B = cpu.getB();
    parse.C = cpu.getC();

    parse.D = cpu.getD();
    parse.E = cpu.getE();
    
    parse.H = cpu.getH();
    parse.L = cpu.getL();

    parse.SP = cpu.getSP();

    parse.PC = cpu.getPC();

    return parse;
} 

void GameBoy::checkIfLogo()
{
    bool check = true;
    
    
    int j = 0;
    for(int i = 0x0104; i < 0x0133; i++)
    {
        if(ROM[i] != logoOG[j++])
            check = false;
    }

    logoPresent = check;
}

void GameBoy::readTitle()
{
    for(int i = 0x0134; i < 0x0143; i++)
    {
        title.push_back(ROM[i]);
    }
}

void GameBoy::checkCGB()
{
    CGB = (ROM[0x0143] & 0b1011111) == 0x80;
}

void GameBoy::readVersion()
{
    version = ROM[0x014C];
}

void GameBoy::verifyChecksum()
{
    unsigned char checksum = 0;

    for(unsigned short address = 0x0134; address <= 0x014C; address++)
        checksum = checksum - ROM[address] - 1;
    
    checksumCorrect = checksum == ROM[0x014D];
}
