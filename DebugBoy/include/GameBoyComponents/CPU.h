#pragma once

class CPU
{
    // CPU Registers
    // 16-bit Registers
    short AF {}; // Accumulator and Flags. High byte is A. Lower 8 bits are Flags Register.
    // Bit 7 -> Zero Flag (Z)
    // Bit 6 -> Substraction Flag (BCD)
    // Bit 5 -> Half Carry Flag (BCD)
    // Bit 4 -> Carry Flag
    // ---------------------------------------------------------
    // All registers below can be split into High and Low bytes.
    // Those are general purpose registers
    short BC {};
    short DE {};
    short HL {};
    // ---------------------------------------------------------
    short SP {}; // Stack Pointer
    short PC {}; // Program Counter

    // Functions to get High and Low Bytes will be needed
    char High(short register);
    char Low(short register);

public:
    CPU();
};