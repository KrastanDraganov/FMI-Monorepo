#pragma once

#include <iostream>

class Matrix
{
public:
    Matrix();

    Matrix(int rows, int columns);

    Matrix(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    ~Matrix();

    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
    Matrix &operator*=(const Matrix &rhs);

    friend bool operator==(const Matrix &lhs, const Matrix &rhs);

private:
    int rows;
    int columns;

    int **matrix;

    void allocateMatrixMemory(int rows, int columns);
    void deleteMatrixMemory();

    void copyFrom(const Matrix &other);
    void free();
};

Matrix &operator+(const Matrix &lhs, const Matrix &rhs);
Matrix &operator-(const Matrix &lhs, const Matrix &rhs);
Matrix &operator*(const Matrix &lhs, const Matrix &rhs);