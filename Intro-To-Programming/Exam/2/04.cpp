#include <iostream>

using namespace std;

const int MATRIX_SIZE = 5;

void mySwap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

bool isValidInput(const int matrix[][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            if (matrix[i][j] == 0)
            {
                return false;
            }
        }
    }

    return true;
}

bool areRowsLinear(const int matrix[][MATRIX_SIZE], int row1, int row2)
{
    int firstNumberRow1 = matrix[row1][0];
    int firstNumberRow2 = matrix[row2][0];

    if (firstNumberRow1 > firstNumberRow2)
    {
        swap(firstNumberRow1, firstNumberRow2);
    }

    bool isDivisble = (firstNumberRow2 % firstNumberRow1 == 0);

    if (!isDivisble)
    {
        return false;
    }

    int targetK = firstNumberRow2 / firstNumberRow1;

    for (int i = 1; i < MATRIX_SIZE; ++i)
    {
        int currentNumberRow1 = matrix[row1][i];
        int currentNumberRow2 = matrix[row2][i];

        if (currentNumberRow1 > currentNumberRow2)
        {
            swap(currentNumberRow1, currentNumberRow2);
        }

        bool isTargetK = (currentNumberRow2 % currentNumberRow1 != 0 || currentNumberRow2 / currentNumberRow1 != targetK);

        if (isTargetK)
        {
            return false;
        }
    }

    return true;
}

bool linear(const int matrix[][MATRIX_SIZE])
{
    for (int row1 = 0; row1 < MATRIX_SIZE; ++row1)
    {
        for (int row2 = row1 + 1; row2 < MATRIX_SIZE; ++row2)
        {
            if (areRowsLinear(matrix, row1, row2))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {{1, 2, 1, 2, 1},
                                            {1, 2, 3, 4, 5},
                                            {1, 1, 1, 1, 1},
                                            {5, 4, 3, 2, 1},
                                            {3, 6, 3, 6, 3}};

    if (!isValidInput(matrix))
    {
        cout << "The input is invalid because it contains 0!\n";
        return 1;
    }

    if (linear(matrix))
    {
        cout << "The matrix is linear combination :)\n";
    }
    else
    {
        cout << "The matrix is NOT linear combination!\n";
    }

    return 0;
}