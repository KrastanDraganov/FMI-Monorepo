#include <iostream>
#include <cstring>

#include "MonsterCard.h"

void MonsterCard::copyFrom(const MonsterCard &other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    attackPoints = other.attackPoints;
    defensePoints = other.defensePoints;
}

void MonsterCard::free()
{
    if (name)
    {
        delete[] name;
    }

    name = nullptr;
    attackPoints = 0;
    defensePoints = 0;
}

MonsterCard::MonsterCard(const MonsterCard &other)
{
    copyFrom(other);
}

MonsterCard &MonsterCard::operator=(const MonsterCard &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

MonsterCard::~MonsterCard()
{
    free();
}

void MonsterCard::setName(const char *newName)
{
    if (!newName || newName == name)
    {
        return;
    }

    delete[] name;

    name = new char[strlen(newName) + 1];
    strcpy(name, newName);
}