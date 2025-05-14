#pragma "once"

#include "Reducer.h"

#include <iostream>

class Accumulator : public Reducer
{
public:
    Accumulator();

    Accumulator(std::function<double(double, double)> customOperator, double initialValue);

    double compute() const override;

private:
    double initialValue;

    std::function<double(double, double)> customOperator;
};