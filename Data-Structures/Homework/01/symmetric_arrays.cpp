#include <iostream>
#include <stack>

bool isArraySymmetric(const int *numbers, int n)
{
    if (!numbers)
    {
        return true;
    }

    std::stack<int> positiveNumbers;

    for (int i = 0; i < n; ++i)
    {
        if (numbers[i] == 0)
        {
            return false;
        }

        if (numbers[i] > 0)
        {
            positiveNumbers.push(numbers[i]);
            continue;
        }

        if (positiveNumbers.empty() || positiveNumbers.top() != -numbers[i])
        {
            return false;
        }

        positiveNumbers.pop();
    }

    return positiveNumbers.empty();
}

int main()
{
    int n;
    std::cin >> n;

    int *numbers = new int[n];

    for (int i = 0; i < n; i++)
    {
        std::cin >> numbers[i];
    }

    std::cout << isArraySymmetric(numbers, n) << std::endl;

    delete[] numbers;

    return 0;
}