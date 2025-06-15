#pragma once

#include "Set.h"

class DifferenceSet : public Set
{
public:
    DifferenceSet() = default;

    DifferenceSet(const Set *a, const Set *b);

    bool contains(int element) const override;

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;

    Set *clone() const override;

    ~DifferenceSet();

private:
    Set *left = nullptr;
    Set *right = nullptr;

    void free();
};