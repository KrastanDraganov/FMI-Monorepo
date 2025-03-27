#pragma once

class MonsterCard
{
private:
    char *name = nullptr;
    unsigned int attackPoints = 0;
    unsigned int defensePoints = 0;

    void copyFrom(const MonsterCard &other);

    void free();

public:
    MonsterCard() = default;

    MonsterCard(const MonsterCard &other);

    MonsterCard &operator=(const MonsterCard &other);

    ~MonsterCard();

    void setName(const char *newName);
};