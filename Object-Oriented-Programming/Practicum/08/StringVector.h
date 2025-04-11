#pragma once

#include "MyString.h"

class StringVector
{
public:
    StringVector() = default;

    StringVector(const StringVector &other);
    StringVector &operator=(const StringVector &other);
    ~StringVector();

    void push_back(const MyString &newString);
    void pop_back();

    void insert(const MyString &newString, int index);
    void erase(int index);

    void clear();

    bool empty();

    int getSize();

    MyString &operator[](int index);
    MyString operator[](int index) const;

private:
    int capacity = 0;
    int size = 0;

    MyString *strings = nullptr;

    void copyFrom(const StringVector &other);
    void free();

    void createNewVector();

    void resize();
    void shrink();
};