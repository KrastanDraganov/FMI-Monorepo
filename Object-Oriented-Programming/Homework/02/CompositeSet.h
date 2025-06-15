#pragma once

#include "Set.h"
#include "MyVector.hpp"

class CompositeSet : public Set
{
public:
    CompositeSet() = default;

    CompositeSet(const MyVector<Set *> &inputSets);

    ~CompositeSet();

protected:
    MyVector<Set *> sets;

    void clear();
};