#include "VectorWriter.h"

void VectorWriter::copyFrom(const VectorWriter &other)
{
    size = other.size;
    capacity = other.capacity;
    indexToAdd = other.indexToAdd;

    numbers = new int[capacity];

    for (int i = 0; i < size; ++i)
    {
        numbers[i] = other.numbers[i];
    }
}

void VectorWriter::moveFrom(VectorWriter &&other)
{
    size = other.size;
    capacity = other.capacity;
    indexToAdd = other.indexToAdd;

    numbers = other.numbers;
    other.numbers = nullptr;
}

void VectorWriter::resize()
{
    capacity *= 2;

    int *newNumbers = new int[capacity];

    for (int i = 0; i < size; ++i)
    {
        newNumbers[i] = numbers[i];
    }

    delete[] numbers;
    numbers = newNumbers;
}

void VectorWriter::free()
{
    delete[] numbers;

    size = 0;
    capacity = 0;
    indexToAdd = 0;
}

VectorWriter::VectorWriter(int size)
{
    this->size = size;
    this->capacity = size * 2;
    this->indexToAdd = 0;

    this->numbers = new int[capacity];
}

VectorWriter::VectorWriter(const VectorWriter &other)
{
    copyFrom(other);
}

VectorWriter &VectorWriter::operator=(const VectorWriter &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

VectorWriter::VectorWriter(VectorWriter &&other) noexcept
{
    moveFrom(std::move(other));
}

VectorWriter &VectorWriter::operator=(VectorWriter &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

VectorWriter::~VectorWriter()
{
    free();
}

int VectorWriter::getSize() const
{
    return size;
}

int &VectorWriter::operator[](int index)
{
    return numbers[index];
}

int VectorWriter::operator[](int index) const
{
    return numbers[index];
}

VectorWriter &operator<<(VectorWriter &os, int newNumber)
{
    os.addElement(newNumber);
}

VectorWriter &operator<<(VectorWriter &os, const VectorWriter &newVector)
{
    for (int i = 0; i < newVector.getSize(); ++i)
    {
        os.addElement(newVector[i]);
    }
}

void VectorWriter::shift()
{
    for (int i = size; i > indexToAdd; ++i)
    {
        numbers[i] = numbers[i - 1];
    }
}

void VectorWriter::seek(int index)
{
    if (size == capacity)
    {
        resize();
    }

    indexToAdd = index;
    shift();
}

void VectorWriter::addElement(int newNumber)
{
    if (size == capacity)
    {
        resize();
    }

    shift();

    numbers[indexToAdd] = newNumber;
}
