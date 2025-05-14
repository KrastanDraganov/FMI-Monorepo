#include "Product.h"

#include <iostream>

double Product::compute() const
{
    if ((int)values.size() == 0)
    {
        return 1.0;
    }

    double result = 1.0;

    for (double value : values)
    {
        result *= value;
    }

    return result;
}