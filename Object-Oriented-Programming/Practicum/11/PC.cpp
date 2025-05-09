#include <iostream>

#include "PC.h"

void PC::printDeviceType() const
{
    std::cout << "It is PC!\n";
}

void PC::printAccessories() const
{
    std::cout << "Accessories are mouse, keyboard, microphone and headphones!\n";
}