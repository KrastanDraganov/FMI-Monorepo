#include <iostream>

#include "Deck.h"

int Deck::getMonsterCount() const
{
    return monstersCount;
}

int Deck::getSpellsCount() const
{
    return spellsCount;
}

bool Deck::addMonsterCardAtBack(const MonsterCard &newMonsterCard)
{
    if (monstersCount == MAX_DECK_SIZE)
    {
        return false;
    }

    monsters[monstersCount] = newMonsterCard;
    ++monstersCount;

    return true;
}

bool Deck::addSpellCardAtBack(const SpellCard &newSpellCard)
{
    if (spellsCount == MAX_DECK_SIZE)
    {
        return false;
    }

    spells[spellsCount] = newSpellCard;
    ++spellsCount;

    return true;
}

bool Deck::changeMonsterCard(const MonsterCard &newMonsterCard, int index)
{
    if (index >= monstersCount)
    {
        return false;
    }

    monsters[index] = newMonsterCard;

    return true;
}

bool Deck::changeSpellCard(const SpellCard &newSpellCard, int index)
{
    if (index >= spellsCount)
    {
        return false;
    }

    spells[index] = newSpellCard;

    return true;
}

bool Deck::removeMonsterCard(int index)
{
    if (index >= monstersCount)
    {
        return false;
    }

    for (int i = index; i < monstersCount - 1; ++i)
    {
        monsters[i] = monsters[i + 1];
    }

    --monstersCount;

    return true;
}

bool Deck::removeSpellCard(int index)
{
    if (index >= spellsCount)
    {
        return false;
    }

    for (int i = index; i < spellsCount - 1; ++i)
    {
        spells[i] = spells[i + 1];
    }

    --spellsCount;

    return true;
}

void Deck::sortMonsterCards(bool (*predicate)(const MonsterCard &, const MonsterCard &))
{
    for (int i = 0; i < monstersCount - 1; ++i)
    {
        int minIndex = i;
        for (unsigned j = i + 1; j < monstersCount; ++j)
        {
            if (predicate(monsters[j], monsters[minIndex]))
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            std::swap(monsters[i], monsters[minIndex]);
        }
    }
}