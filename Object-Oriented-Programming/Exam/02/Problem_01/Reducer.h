#pragma once

#include <vector>

class Reducer
{
public:
    void add(double newValue);

    virtual double compute() const = 0;

protected:
    std::vector<double> values;
};