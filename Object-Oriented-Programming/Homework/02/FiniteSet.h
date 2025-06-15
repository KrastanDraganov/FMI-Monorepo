#pragma once

#include "Set.h"
#include "MyVector.hpp"

class FiniteSet : public Set
{
public:
    FiniteSet() = default;

    FiniteSet(const MyVector<int> &elements);

    bool contains(int element) const override;

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;

    Set *clone() const override;

private:
    MyVector<int> elements;
};
