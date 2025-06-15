#pragma once

#include "Set.h"

class BiggerSet : public Set
{
public:
    BiggerSet() = default;

    BiggerSet(int threshold);

    bool contains(int element) const override;

    void serialize(std::ostream &out) const override;
    void deserialize(std::istream &in) override;

    Set *clone() const override;

private:
    int threshold = 0;
};