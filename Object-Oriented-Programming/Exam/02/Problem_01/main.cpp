#include "Reducer.h"
#include "Product.h"
#include "CountAbove.h"
#include "Accumulator.h"

double process(const std::vector<double> &data, Reducer *comb)
{
    for (double value : data)
    {
        comb->add(value);
    }

    return comb->compute();
}

int main()
{
    Accumulator *r = new Accumulator([](double a, double b)
                                     { return a + b; }, 0);

    std::cout << process({10, 2, 1}, r);

    std::cout << process({1, 2, 3, 4}, new Product);

    delete r;

    return 0;
}