#pragma once

#include "Reducer.h"

class Product : public Reducer
{
public:
    double compute() const override;
};