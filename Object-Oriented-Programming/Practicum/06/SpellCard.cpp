#include <iostream>
#include <cstring>

#include "SpellCard.h"

SpellCard::SpellCard(const char *name, const char *effect)
{
    setName(name);
    setEffect(effect);
}

void SpellCard::setName(const char *newName)
{
    if (!newName || strlen(newName) > MAX_NAME_LENGTH)
    {
        return;
    }

    strcpy(name, newName);
}

void SpellCard::setEffect(const char *newEffect)
{
    if (!newEffect || strlen(newEffect) > MAX_EFFECT_LENGTH)
    {
        return;
    }

    strcpy(effect, newEffect);
}

const char *SpellCard::getName() const
{
    return name;
}

const char *SpellCard::getEffect() const
{
    return effect;
}