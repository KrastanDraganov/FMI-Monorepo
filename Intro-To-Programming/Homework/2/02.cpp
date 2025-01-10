#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>

using namespace std;

const int BOMB = -1;

const int BOARD_SIZE_LOWER_BOUND = 4;
const int BOARD_SIZE_UPPER_BOUND = 100;

const int ALL_DIRECTIONS = 8;
const int COORDINATES = 2;

const int directions[ALL_DIRECTIONS][COORDINATES] =
    {{0, -1},
     {0, +1},
     {-1, 0},
     {+1, 0},
     {-1, -1},
     {-1, +1},
     {+1, -1},
     {+1, +1}};

bool isValidBoardSize(int x)
{
    return (x >= BOARD_SIZE_LOWER_BOUND && x <= BOARD_SIZE_UPPER_BOUND);
}

bool isValidCoordinate(int x, int y, int rows, int columns)
{
    return (x >= 0 && x < rows && y >= 0 && y < columns);
}

int getCoordinateValue(int x, int y)
{
    return x * BOARD_SIZE_UPPER_BOUND + y;
}

bool isMyStackEmpty(int stackEnd)
{
    return stackEnd == -1;
}

void myStackPush(int myStack[], int newElement, int &stackEnd)
{
    ++stackEnd;
    myStack[stackEnd] = newElement;
}

int myStackPop(const int myStack[], int &stackEnd)
{
    int topElement = myStack[stackEnd];

    --stackEnd;

    return topElement;
}

bool **createBoolMatrix(int rows, int columns)
{
    bool **matrix = new bool *[rows];

    for (int row = 0; row < rows; ++row)
    {
        matrix[row] = new bool[columns];

        for (int col = 0; col < columns; ++col)
        {
            matrix[row][col] = false;
        }
    }

    return matrix;
}

void deleteBooleanMatrix(bool **matrix, int rows)
{
    for (int row = 0; row < rows; ++row)
    {
        delete[] matrix[row];
    }

    delete[] matrix;
}

int countBombsAround(int x, int y, int rows, int columns, bool **isBomb)
{
    int counter = 0;

    for (int i = 0; i < ALL_DIRECTIONS; ++i)
    {
        int nextX = x + directions[i][0];
        int nextY = y + directions[i][1];

        if (isValidCoordinate(nextX, nextY, rows, columns))
        {
            counter += isBomb[nextX][nextY];
        }
    }

    return counter;
}

void placeBombs(int **board, int rows, int columns, int allBombsCount)
{
    bool **isBomb = createBoolMatrix(rows, columns);

    int placedBombsCount = 0;

    while (placedBombsCount < allBombsCount)
    {
        int currentBombX = rand() % rows;
        int currentBomxY = rand() % columns;

        if (isBomb[currentBombX][currentBomxY])
        {
            continue;
        }

        board[currentBombX][currentBomxY] = BOMB;
        isBomb[currentBombX][currentBomxY] = true;

        ++placedBombsCount;
    }

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            if (!isBomb[row][col])
            {
                board[row][col] = countBombsAround(row, col, rows, columns, isBomb);
            }
        }
    }

    deleteBooleanMatrix(isBomb, rows);
}

int **createBoard(int rows, int columns, int bombsCount)
{
    int **board = new int *[rows];

    for (int row = 0; row < rows; ++row)
    {
        board[row] = new int[columns];

        for (int col = 0; col < columns; ++col)
        {
            board[row][col] = 0;
        }
    }

    placeBombs(board, rows, columns, bombsCount);

    return board;
}

void deleteBoard(int **board, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] board[i];
    }

    delete[] board;
}

void printBoard(int **board, bool **visited, int rows, int columns)
{
    cout << "\n  ";

    for (int col = 1; col <= columns; ++col)
    {
        cout << col << " ";
    }

    cout << endl;

    for (int row = 0; row < rows; ++row)
    {
        cout << row + 1 << " ";

        for (int col = 0; col < columns; ++col)
        {
            if (!visited[row][col])
            {
                cout << ".";
            }
            else if (board[row][col] == BOMB)
            {
                cout << "$";
            }
            else
            {
                cout << board[row][col];
            }

            cout << " ";
        }

        cout << endl;
    }

    cout << endl;
}

void pushAdjacentCellsInStack(int x, int y, int **board, bool **visited, bool **isInStack,
                              int rows, int columns, int myStack[], int &stackEnd)
{
    for (int i = 0; i < ALL_DIRECTIONS; ++i)
    {
        int nextX = x + directions[i][0];
        int nextY = y + directions[i][1];

        if (!isValidCoordinate(nextX, nextY, rows, columns))
        {
            continue;
        }

        if (visited[nextX][nextY] || isInStack[nextX][nextY])
        {
            continue;
        }

        int nextCoordinate = getCoordinateValue(nextX, nextY);

        myStackPush(myStack, nextCoordinate, stackEnd);
        isInStack[nextX][nextY] = true;
    }
}

void markCells(int startX, int startY, int **board, bool **visited, int rows,
               int columns, bool &hitBomb, int &leftCellsToMark)
{
    if (visited[startX][startY])
    {
        cout << "\nYou already marked this cell!\n";

        return;
    }

    int *myStack = new int[rows * columns];
    int stackEnd = -1;

    bool **isInStack = createBoolMatrix(rows, columns);

    int startCoordinate = getCoordinateValue(startX, startY);

    myStackPush(myStack, startCoordinate, stackEnd);
    isInStack[startX][startY] = true;

    while (!isMyStackEmpty(stackEnd))
    {
        int currentCoordinate = myStackPop(myStack, stackEnd);

        int currentX = currentCoordinate / BOARD_SIZE_UPPER_BOUND;
        int currentY = currentCoordinate % BOARD_SIZE_UPPER_BOUND;

        isInStack[currentX][currentY] = false;

        visited[currentX][currentY] = true;
        --leftCellsToMark;

        if (board[currentX][currentY] == BOMB)
        {
            hitBomb = true;

            return;
        }

        if (board[currentX][currentY] == 0)
        {
            pushAdjacentCellsInStack(currentX, currentY, board, visited, isInStack,
                                     rows, columns, myStack, stackEnd);
        }
    }

    delete[] myStack;
    deleteBooleanMatrix(isInStack, rows);
}

void playGame(int rows, int columns, int bombsCount)
{
    int **board = createBoard(rows, columns, bombsCount);

    bool **visited = createBoolMatrix(rows, columns);

    printBoard(board, visited, rows, columns);

    int leftCellsToMark = rows * columns - bombsCount;

    bool hitBomb = false;

    do
    {
        cout << "Enter coordinates: ";

        int x, y;
        cin >> x >> y;

        system("clear");

        --x;
        --y;

        if (isValidCoordinate(x, y, rows, columns))
        {
            markCells(x, y, board, visited, rows, columns, hitBomb, leftCellsToMark);
        }
        else
        {
            cout << "\nNot a valid coordinates in the size of the board!\n";
        }

        printBoard(board, visited, rows, columns);
    } while (!hitBomb && leftCellsToMark > 0);

    if (hitBomb)
    {
        cout << "You hit a bomb. You lose!\n";
    }
    else
    {
        cout << "You win!\n";
    }

    deleteBooleanMatrix(visited, rows);
    deleteBoard(board, rows);
}

int main()
{
    srand(time(nullptr));

    int m, n;

    do
    {
        cout << "\nConstraints for board size: 4 <= n, m <= 100\n";
        cout << "Enter board sizes m and n: ";

        cin >> m >> n;

        system("clear");
    } while (!isValidBoardSize(n) || !isValidBoardSize(m));

    int bombsLimit = sqrt(m * n);
    int bombsCount = -1;

    do
    {
        cout << "\nConstraints for number of bombs is: 0 <= bombs <= " << bombsLimit << endl;
        cout << "Enter number of bombs: ";

        cin >> bombsCount;

        system("clear");
    } while (bombsCount < 0 || bombsCount > bombsLimit);

    playGame(n, m, bombsCount);

    return 0;
}