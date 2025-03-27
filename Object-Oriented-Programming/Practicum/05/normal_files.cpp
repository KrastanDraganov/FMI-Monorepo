#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_MATRIX_SIZE = 20;

const int MAX_LEN = MAX_MATRIX_SIZE * 2 * 9;

const char ROW_DELIMETER = '|';

const char COLUMN_DELIMETER = ',';

class Matrix
{
private:
    int rows, cols;
    int values[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

public:
    Matrix() = default;

    bool readFromFile(std::ifstream &inputFile)
    {
        if (!inputFile.is_open())
        {
            return false;
        }

        char currentRowValues[MAX_LEN];
        char currentNumber[MAX_LEN];

        int currentRowIndex = 0;
        int currentColumnIndex = 0;

        while (inputFile.getline(currentRowValues, MAX_LEN, ROW_DELIMETER))
        {
            int currentNumber = 0;
            int currentRowSize = strlen(currentRowValues);

            for (int i = 0; i <= currentRowSize; ++i)
            {
                if (i < currentRowSize && currentRowValues[i] != COLUMN_DELIMETER)
                {
                    currentNumber = 10 * currentNumber + (currentRowValues[i] - '0');
                    continue;
                }

                this->values[currentRowIndex][currentColumnIndex] = currentNumber;

                ++currentColumnIndex;
                currentNumber = 0;
            }

            bool isFirstRow = (currentRowIndex == 0);

            if (isFirstRow)
            {
                this->cols = currentColumnIndex;
            }

            ++currentRowIndex;
            currentColumnIndex = 0;
        }

        this->rows = currentRowIndex;

        return true;
    }
};

int getFileSize(std::ifstream &inFile)
{
    if (!inFile.is_open())
    {
        return 0;
    }

    int startPosition = inFile.tellg();

    inFile.seekg(0, std::ios::end);

    int fileSize = inFile.tellg();

    inFile.seekg(startPosition);

    return fileSize;
}

void simulateFileSize()
{
    std::ifstream inMyFile("my_file");

    std::cout << getFileSize(inMyFile) << std::endl;

    inMyFile.close();
}

void readAndWriteToFile()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    std::ofstream outMyResult("result.txt");

    if (!outMyResult.is_open())
    {
        return;
    }

    outMyResult << a + b + c << std::endl;
    outMyResult << a * b * c << std::endl;

    outMyResult.close();

    std::ifstream inMyResult("result.txt");

    if (!inMyResult.is_open())
    {
        return;
    }

    int sum, product;
    inMyResult >> sum >> product;

    std::cout << "Sum is " << sum << std::endl;
    std::cout << "Product is " << product << std::endl;
}

void simulateMultiplyingMatrices()
{
    std::ifstream inMatrixFile("matrix");

    Matrix matrix1;
    matrix1.readFromFile(inMatrixFile);
}

int main()
{
    // simulateFileSize();

    // readAndWriteToFile();

    simulateMultiplyingMatrices();

    return 0;
}