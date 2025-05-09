#include <iostream>
#include <cstring>

#include "Computer.h"

void Computer::copyFrom(const Computer &other)
{
    power = other.power;
    ramCapacity = other.ramCapacity;
    processorPower = other.processorPower;

    graphicCardName = new char[strlen(other.graphicCardName) + 1];
    strcpy(graphicCardName, other.graphicCardName);
}

void Computer::moveFrom(Computer &&other)
{
    power = other.power;
    ramCapacity = other.ramCapacity;
    processorPower = other.processorPower;

    graphicCardName = other.graphicCardName;
    graphicCardName = nullptr;
}

void Computer::free()
{
    power = 0;
    ramCapacity = 0;
    processorPower = 0.0;

    delete[] graphicCardName;
    graphicCardName = nullptr;
}

Computer::Computer(const Computer &other)
{
    copyFrom(other);
}

Computer &Computer::operator=(const Computer &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Computer::Computer(Computer &&other) noexcept
{
    moveFrom(std::move(other));
}

Computer &Computer::operator=(Computer &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

Computer::~Computer()
{
    free();
}

void Computer::setPower(int newPower)
{
    power = newPower;
}

void Computer::setRamCapacity(int newRamCapacity)
{
    ramCapacity = newRamCapacity;
}

void Computer::setProcessorPower(double newProcessorPower)
{
    processorPower = newProcessorPower;
}

void Computer::setGraphicCardName(const char *newGraphicCardName)
{
    delete[] graphicCardName;

    graphicCardName = new char[strlen(newGraphicCardName) + 1];
    strcpy(graphicCardName, newGraphicCardName);
}

int Computer::getPower() const
{
    return power;
}

int Computer::getRamCapacity() const
{
    return ramCapacity;
}

double Computer::getProcessorPower() const
{
    return processorPower;
}

char *Computer::getGraphicCardName() const
{
    return graphicCardName;
}