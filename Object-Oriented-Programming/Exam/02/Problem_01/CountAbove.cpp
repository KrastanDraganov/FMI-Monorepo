#include "CountAbove.h"

CountAbove::CountAbove() : Reducer()
{
}

CountAbove::CountAbove(int threshold) : Reducer()
{
    this->threshold = threshold;
}

double CountAbove::compute() const
{
    int counter = 0;

    for (double value : values)
    {
        if (value > threshold)
        {
            ++counter;
        }
    }

    return counter;
}