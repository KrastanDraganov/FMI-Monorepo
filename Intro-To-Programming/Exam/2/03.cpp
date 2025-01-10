#include <iostream>

using namespace std;

int findMaxProduct(const int numbers[], unsigned numbersSize, int multiplier)
{
    int maxProduct = 0;

    for (int i = 0; i < numbersSize; ++i)
    {
        int currentProduct = numbers[i] * multiplier;

        if (i == 0 || currentProduct > maxProduct)
        {
            maxProduct = currentProduct;
        }
    }

    return maxProduct;
}

int maxpair(const int a[], unsigned na, const int b[], unsigned nb)
{
    int result = 0;

    for (int i = 0; i < na; ++i)
    {
        int currentMaxProduct = findMaxProduct(b, nb, a[i]);

        if (i == 0 || currentMaxProduct > result)
        {
            result = currentMaxProduct;
        }
    }

    return result;
}

int main()
{
    constexpr unsigned na = 2;
    int a[na] = {-1, 10};

    constexpr unsigned nb = 3;
    int b[nb] = {0, -100, 2};

    cout << maxpair(a, na, b, nb) << endl;

    return 0;
}