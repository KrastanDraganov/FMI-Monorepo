#pragma once

#include "Set.h"
#include "SetUtils.h"

class SymmetricalDifferenceSet : public Set
{
public:
    SymmetricalDifferenceSet() = default;

    SymmetricalDifferenceSet(const Set *a, const Set *b);

    bool contains(int element) const override;

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;

    Set *clone() const override;

    ~SymmetricalDifferenceSet();

private:
    Set *left = nullptr;
    Set *right = nullptr;

    void free();
};