#include "BiggerSet.h"
#include "SetUtils.h"

BiggerSet::BiggerSet(int threshold)
{
    this->threshold = threshold;
}

bool BiggerSet::contains(int element) const
{
    return element > threshold;
}

void BiggerSet::serialize(std::ostream &out) const
{
    if (!out)
    {
        return;
    }

    out << setTypeToChar(SetType::BiggerSet) << "\n";
    out << threshold << "\n";
}

void BiggerSet::deserialize(std::istream &in)
{
    if (!in)
    {
        return;
    }

    in >> threshold;
}

Set *BiggerSet::clone() const
{
    return new BiggerSet(*this);
}