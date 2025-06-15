#include "CompositeSet.h"

CompositeSet::CompositeSet(const MyVector<Set *> &inputSets)
{
    clear();

    for (size_t i = 0; i < inputSets.getSize(); ++i)
    {
        sets.push_back(inputSets[i]->clone());
    }
}

void CompositeSet::clear()
{
    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        delete sets[i];
    }

    sets.clear();
}

CompositeSet::~CompositeSet()
{
    clear();
}