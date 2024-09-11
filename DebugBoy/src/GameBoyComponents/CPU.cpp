#include "CPU.h"

char CPU::High(short registry)
{
    return (char) registry << 8;
}

char CPU::Low(short registry)
{
    return (char) registry;
}

