#pragma once

#include <iostream>
#include <fstream>

class Set
{
public:
    virtual bool contains(int element) const = 0;

    virtual void serialize(std::ostream &out) const = 0;
    virtual void deserialize(std::istream &in) = 0;

    virtual Set *clone() const = 0;

    virtual ~Set() = default;
};

enum class SetType
{
    FiniteSet,
    BiggerSet,
    UnionSet,
    IntersectionSet,
    DifferenceSet,
    SymmetricalDifferenceSet,
    Unknown
};