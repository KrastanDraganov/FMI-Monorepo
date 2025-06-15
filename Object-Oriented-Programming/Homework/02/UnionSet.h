#pragma once

#include "CompositeSet.h"

class UnionSet : public CompositeSet
{
public:
    bool contains(int element) const override;

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;

    Set *clone() const override;
};