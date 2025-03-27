#pragma once

const int MAX_NAME_LENGTH = 25;
const int MAX_EFFECT_LENGTH = 100;

class SpellCard
{
private:
    char name[MAX_NAME_LENGTH] = "";
    char effect[MAX_EFFECT_LENGTH] = "";

public:
    SpellCard() = default;

    SpellCard(const char *name, const char *effect);

    void setName(const char *newName);

    void setEffect(const char *newEffect);

    const char *getName() const;

    const char *getEffect() const;
};