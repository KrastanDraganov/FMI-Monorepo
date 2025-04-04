#include "Matrix.h"

void Matrix::allocateMatrixMemory(int rows, int columns)
{
    matrix = new int *[rows];
    for (int row = 0; row < rows; ++row)
    {
        matrix[row] = new int[columns];
    }
}

void Matrix::deleteMatrixMemory()
{
    if (matrix)
    {
        for (int row = 0; row < rows; ++row)
        {
            if (matrix[row])
            {
                delete[] matrix[row];
                matrix[row] = nullptr;
            }
        }

        delete[] matrix;
        matrix = nullptr;
    }
}

void Matrix::copyFrom(const Matrix &other)
{
    rows = other.rows;
    columns = other.columns;

    allocateMatrixMemory(rows, columns);

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            matrix[row][col] = other.matrix[row][col];
        }
    }
}

void Matrix::free()
{
    deleteMatrixMemory();
    rows = 0;
    columns = 0;
}

Matrix::Matrix(const Matrix &other)
{
    copyFrom(other);
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Matrix::~Matrix()
{
    free();
}

Matrix::Matrix() : Matrix(2, 2)
{
}

Matrix::Matrix(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;

    allocateMatrixMemory(rows, columns);
}

Matrix &Matrix::operator+=(const Matrix &rhs)
{
    if (rows != rhs.rows || columns != rhs.columns)
    {
        return *this;
    }

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            matrix[row][col] += rhs.matrix[row][col];
        }
    }

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs)
{
    if (rows != rhs.rows || columns != rhs.columns)
    {
        return *this;
    }

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            matrix[row][col] -= rhs.matrix[row][col];
        }
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &rhs)
{
    if (columns != rhs.rows)
    {
        return *this;
    }

    int newRows = rows;
    int newColumns = rhs.columns;

    Matrix result(newRows, newColumns);

    for (int row = 0; row < newRows; ++row)
    {
        for (int col = 0; col < newColumns; ++col)
        {
            for (int i = 0; i < columns; ++i)
            {
                result.matrix[row][col] += matrix[row][i] * matrix[i][col];
            }
        }
    }

    *this = result;

    return *this;
}

Matrix &operator+(const Matrix &lhs, const Matrix &rhs)
{
    Matrix result(lhs);
    result += rhs;

    return result;
}

Matrix &operator-(const Matrix &lhs, const Matrix &rhs)
{
    Matrix result(lhs);
    result -= rhs;

    return result;
}

Matrix &operator*(const Matrix &lhs, const Matrix &rhs)
{
    Matrix result(lhs);
    result *= rhs;

    return result;
}