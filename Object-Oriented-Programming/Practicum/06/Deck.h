#pragma once

#include "MonsterCard.h"
#include "SpellCard.h"

const int MAX_DECK_SIZE = 20;

class Deck
{
private:
    int monstersCount = 0;
    int spellsCount = 0;

    MonsterCard monsters[MAX_DECK_SIZE];
    SpellCard spells[MAX_DECK_SIZE];

public:
    Deck() = default;

    int getMonsterCount() const;
    int getSpellsCount() const;

    bool addMonsterCardAtBack(const MonsterCard &newMonsterCard);
    bool addSpellCardAtBack(const SpellCard &newSpellCard);

    bool changeMonsterCard(const MonsterCard &newMonsterCard, int index);
    bool changeSpellCard(const SpellCard &newSpellCard, int index);

    bool removeMonsterCard(int index);
    bool removeSpellCard(int index);

    void sortMonsterCards(bool (*predicate)(const MonsterCard &, const MonsterCard &));
};