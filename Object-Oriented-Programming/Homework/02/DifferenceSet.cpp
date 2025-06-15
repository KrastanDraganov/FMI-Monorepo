#include "DifferenceSet.h"
#include "SetUtils.h"

DifferenceSet::DifferenceSet(const Set *a, const Set *b)
{
    left = a->clone();
    right = b->clone();
}

void DifferenceSet::free()
{
    delete left;
    left = nullptr;

    delete right;
    right = nullptr;
}

bool DifferenceSet::contains(int element) const
{
    return left && right && left->contains(element) && !right->contains(element);
}

void DifferenceSet::serialize(std::ostream &out) const
{
    if (!out)
    {
        return;
    }

    out << setTypeToChar(SetType::DifferenceSet) << "\n";

    left->serialize(out);
    right->serialize(out);
}

void DifferenceSet::deserialize(std::istream &in)
{
    if (!in)
    {
        return;
    }

    free();

    char typeCharacter;

    in.get(typeCharacter);
    in.ignore();

    SetType type = charToSetType(typeCharacter);
    left = createSetByType(type);

    if (left)
    {
        left->deserialize(in);
    }

    in.get(typeCharacter);
    in.ignore();

    type = charToSetType(typeCharacter);
    right = createSetByType(type);

    if (right)
    {
        right->deserialize(in);
    }
}

Set *DifferenceSet::clone() const
{
    return new DifferenceSet(*this);
}

DifferenceSet::~DifferenceSet()
{
    free();
}