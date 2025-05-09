#pragma once

#include "Computer.h"

class PC : public Computer
{
public:
    void printDeviceType() const override;
    void printAccessories() const override;
};