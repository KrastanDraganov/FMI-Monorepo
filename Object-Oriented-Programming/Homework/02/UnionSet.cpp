#include "UnionSet.h"
#include "SetUtils.h"

bool UnionSet::contains(int element) const
{
    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        if (sets[i]->contains(element))
        {
            return true;
        }
    }
    return false;
}

void UnionSet::serialize(std::ostream &out) const
{
    if (!out)
    {
        return;
    }

    out << setTypeToChar(SetType::UnionSet) << "\n";
    out << (int)sets.getSize() << "\n";

    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        sets[i]->serialize(out);
    }
}

void UnionSet::deserialize(std::istream &in)
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

Set *UnionSet::clone() const
{
    UnionSet *copy = new UnionSet();

    for (size_t i = 0; i < sets.getSize(); ++i)
    {
        copy->sets.push_back(sets[i]->clone());
    }

    return copy;
}