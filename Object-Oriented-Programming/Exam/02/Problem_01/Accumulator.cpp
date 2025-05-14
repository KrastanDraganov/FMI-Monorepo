#include "Accumulator.h"

Accumulator::Accumulator() : Reducer()
{
}

Accumulator::Accumulator(std::function<double(double, double)> customOperator, double initialValue) : Reducer()
{
    this->initialValue = initialValue;
    this->customOperator = customOperator;
}

double Accumulator::compute() const
{
    double result = initialValue;

    for (double value : values)
    {
        result = customOperator(result, value);
    }

    return result;
}