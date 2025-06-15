#include "IntersectionSet.h"
#include "SetUtils.h"

bool IntersectionSet::contains(int element) const
{
    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        if (!sets[i]->contains(element))
        {
            return false;
        }
    }
    return true;
}

void IntersectionSet::serialize(std::ostream &out) const
{
    if (!out)
    {
        return;
    }

    out << setTypeToChar(SetType::IntersectionSet) << "\n";
    out << sets.getSize() << "\n";

    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        sets[i]->serialize(out);
    }
}

void IntersectionSet::deserialize(std::istream &in)
{
    if (!in)
    {
        return;
    }

    clear();

    size_t count;

    in >> count;
    in.ignore();

    for (size_t i = 0; i < count; ++i)
    {
        char typeCharacter;

        in.get(typeCharacter);
        in.ignore();

        SetType type = charToSetType(typeCharacter);
        Set *s = createSetByType(type);

        if (s)
        {
            s->deserialize(in);
            sets.push_back(s);
        }
    }
}

Set *IntersectionSet::clone() const
{
    IntersectionSet *copy = new IntersectionSet();

    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        copy->sets.push_back(sets[i]->clone());
    }

    return copy;
}