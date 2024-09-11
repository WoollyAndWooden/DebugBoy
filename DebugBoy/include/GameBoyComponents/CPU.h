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
    short PC {0x0100}; // Program Counter

    // Functions to get High and Low Bytes will be needed
    char High(short registry);
    char Low(short registry);

public:
    CPU() {};
    
    char getA() const { return (char) AF; }
    char get_z() const { return AF & 0x0080; }
    char get_n() const { return AF & 0x0040; }
    char get_h() const { return AF & 0x0020; }
    char get_c() const { return AF & 0x0010; }
    char getB() const { return (char) BC; }
    char getC() const { return (char) BC << 8; }
    char getD() const { return (char) DE; }
    char getE() const { return (char) DE << 8; }
    char getH() const { return (char) HL; }
    char getL() const { return (char) HL << 8; }
    short getSP() const { return SP; }
    short getPC() const { return PC; }
};