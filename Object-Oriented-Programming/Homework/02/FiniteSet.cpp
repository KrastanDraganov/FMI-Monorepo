#include "FiniteSet.h"
#include "SetUtils.h"

FiniteSet::FiniteSet(const MyVector<int> &elements)
{
    this->elements.clear();

    for (size_t i = 0; i < elements.getSize(); ++i)
    {
        this->elements.push_back(elements[i]);
    }
}

bool FiniteSet::contains(int element) const
{
    for (size_t i = 0; i < elements.getSize(); ++i)
    {
        if (elements[i] == element)
        {
            return true;
        }
    }

    return false;
}

void FiniteSet::serialize(std::ostream &out) const
{
    if (!out)
    {
        return;
    }

    out << setTypeToChar(SetType::FiniteSet) << "\n";
    out << (int)elements.getSize() << "\n";

    for (size_t i = 0; i < elements.getSize(); ++i)
    {
        out << elements[i] << "\n";
    }
}

void FiniteSet::deserialize(std::istream &in)
{
    if (!in)
    {
        return;
    }

    elements.clear();

    size_t count;
    in >> count;

    for (size_t i = 0; i < count; ++i)
    {
        int value;
        in >> value;

        elements.push_back(value);
    }
}

Set *FiniteSet::clone() const
{
    FiniteSet *copy = new FiniteSet();

    for (size_t i = 0; i < elements.getSize(); ++i)
    {
        copy->elements.push_back(elements[i]);
    }

    return copy;
}