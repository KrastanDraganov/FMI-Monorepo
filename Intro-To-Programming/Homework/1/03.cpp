#include <iostream>

using namespace std;

int pow10(int degree)
{
    if (degree < 0)
    {
        return 0;
    }

    int result = 1;

    for (int i = 0; i < degree; ++i)
    {
        result *= 10;
    }

    return result;
}

bool isBitSet(int mask, int bit)
{
    return (mask & (1 << bit));
}

void setBit(int &mask, int bit)
{
    mask |= (1 << bit);
}

int inputNumberWithLeadingZeroes(int digitsCounter)
{
    int number = 0;

    for (int i = 0; i < digitsCounter; ++i)
    {
        char digit;
        cin >> digit;

        number = 10 * number + (digit - '0');
    }

    return number;
}

int getAndRemoveLastDigit(int &number)
{
    int lastDigit = number % 10;
    number /= 10;

    return lastDigit;
}

bool hasUniqueDigits(int number, int digitsCounter, int &usedDigitsMask)
{
    for (int i = 0; i < digitsCounter; ++i)
    {
        int currentDigit = getAndRemoveLastDigit(number);

        if (isBitSet(usedDigitsMask, currentDigit))
        {
            return false;
        }

        setBit(usedDigitsMask, currentDigit);
    }

    return true;
}

bool meetConditions(int number, int usedDigitsInNumberMask, int guess, int bulls, int cows, int digitsCounter)
{
    for (int i = 0; i < digitsCounter; ++i)
    {
        int currentDigitNumber = getAndRemoveLastDigit(number);
        int currentDigitGuess = getAndRemoveLastDigit(guess);

        if (currentDigitNumber == currentDigitGuess)
        {
            --bulls;
        }
        else if (isBitSet(usedDigitsInNumberMask, currentDigitGuess))
        {
            --cows;
        }
    }

    return (bulls == 0 && cows == 0);
}

bool isSolution(int number, int usedDigitsMask, const int guesses[], const int bulls[], const int cows[], int n, int digitsCounter)
{
    for (int i = 0; i < n; ++i)
    {
        if (!meetConditions(number, usedDigitsMask, guesses[i], bulls[i], cows[i], digitsCounter))
        {
            return false;
        }
    }

    return true;
}

void printFormattedNumber(int number, int leadingZeroTreshold)
{
    bool hasLeadingZero = (number < leadingZeroTreshold);

    if (hasLeadingZero)
    {
        cout << 0;
    }

    cout << number << " ";
}

int main()
{
    int m;
    cin >> m;

    int n;
    cin >> n;

    int guesses[n];
    int bulls[n], cows[n];

    for (int i = 0; i < n; ++i)
    {
        guesses[i] = inputNumberWithLeadingZeroes(m);

        cin >> bulls[i] >> cows[i];
    }

    int possibleSolutionLowerBound = pow10(m - 2);
    int possibleSolutionUpperBound = pow10(m);

    int leadingZeroTreshold = pow10(m - 1);

    for (int number = possibleSolutionLowerBound; number < possibleSolutionUpperBound; ++number)
    {
        int usedDigitsMask = 0;

        if (!hasUniqueDigits(number, m, usedDigitsMask))
        {
            continue;
        }

        if (isSolution(number, usedDigitsMask, guesses, bulls, cows, n, m))
        {
            printFormattedNumber(number, leadingZeroTreshold);
        }
    }

    cout << endl;

    return 0;
}