#pragma once

#include "Reducer.h"

class CountAbove : public Reducer
{
public:
    CountAbove();

    CountAbove(int threshold);

    double compute() const override;

private:
    int threshold;
};