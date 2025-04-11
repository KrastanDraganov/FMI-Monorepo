#include "StringVector.h"

void StringVector::copyFrom(const StringVector &other)
{
    capacity = other.capacity;
    size = other.size;

    strings = new MyString[capacity];

    for (int i = 0; i < size; ++i)
    {
        strings[i] = other.strings[i];
    }
}

void StringVector::free()
{
    if (strings)
    {
        delete[] strings;
        strings = nullptr;
    }

    capacity = 0;
    size = 0;
}

void StringVector::createNewVector()
{
    MyString *newStrings = new MyString[capacity];

    for (int i = 0; i < size; ++i)
    {
        newStrings[i] = strings[i];
    }

    delete[] strings;
    strings = newStrings;
}

void StringVector::resize()
{
    capacity *= 2;
    createNewVector();
}

void StringVector::shrink()
{
    capacity /= 2;
    createNewVector();
}

StringVector::StringVector(const StringVector &other)
{
    copyFrom(other);
}

StringVector &StringVector::operator=(const StringVector &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

StringVector::~StringVector()
{
    free();
}

void StringVector::push_back(const MyString &newString)
{
    if (size == capacity)
    {
        resize();
    }

    strings[size] = newString;
    ++size;
}

void StringVector::pop_back()
{
    if (size == 0)
    {
        return;
    }

    strings[size] = nullptr;
    --size;

    if (size <= capacity / 3)
    {
        shrink();
    }
}

void StringVector::insert(const MyString &newString, int index)
{
    if (index >= size)
    {
        return;
    }

    if (size == capacity)
    {
        resize();
    }

    for (int i = size; i > index; --i)
    {
        strings[i] = strings[i - 1];
    }

    strings[index] = newString;
}

void StringVector::erase(int index)
{
    if (index >= size)
    {
        return;
    }

    for (int i = index; i + 1 < size; ++i)
    {
        strings[i] = strings[i + 1];
    }

    --size;

    if (size <= capacity / 3)
    {
        shrink();
    }
}

void StringVector::clear()
{
    free();
}

bool StringVector::empty()
{
    return (size == 0);
}

int StringVector::getSize()
{
    return size;
}

MyString &StringVector::operator[](int index)
{
    return strings[index];
}
MyString StringVector::operator[](int index) const
{
    return strings[index];
}