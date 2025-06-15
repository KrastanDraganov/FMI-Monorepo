#include "SymmetricalDifferenceSet.h"
#include "SetUtils.h"

SymmetricalDifferenceSet::SymmetricalDifferenceSet(const Set *a, const Set *b)
{
    left = a->clone();
    right = b->clone();
}

void SymmetricalDifferenceSet::free()
{
    delete left;
    left = nullptr;

    delete right;
    right = nullptr;
}

bool SymmetricalDifferenceSet::contains(int element) const
{
    return left && right && (left->contains(element) != right->contains(element));
}

void SymmetricalDifferenceSet::serialize(std::ostream &out) const
{
    if (!out)
    {
        return;
    }

    out << setTypeToChar(SetType::SymmetricalDifferenceSet) << "\n";

    left->serialize(out);
    right->serialize(out);
}

void SymmetricalDifferenceSet::deserialize(std::istream &in)
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

Set *SymmetricalDifferenceSet::clone() const
{
    return new SymmetricalDifferenceSet(*this);
}

SymmetricalDifferenceSet::~SymmetricalDifferenceSet()
{
    free();
}