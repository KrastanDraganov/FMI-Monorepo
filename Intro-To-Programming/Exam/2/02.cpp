#include <iostream>

using namespace std;

void printNumberMultipleTimes(int number, int counter)
{
    for (int i = 0; i < counter; ++i)
    {
        cout << number << " ";
    }
}

void RLE(const unsigned a[], unsigned n)
{
    for (int i = 1; i < n; i += 2)
    {
        printNumberMultipleTimes(a[i], a[i - 1]);
    }

    cout << endl;
}

int main()
{
    constexpr unsigned n = 7;
    unsigned a[n] = {0, 1, 1, 0, 2, 2, 7};

    RLE(a, n);

    return 0;
}