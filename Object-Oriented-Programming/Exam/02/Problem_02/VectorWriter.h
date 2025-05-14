#pragma once

#include <iostream>

class VectorWriter
{
public:
    VectorWriter() = default;

    VectorWriter(int size);

    VectorWriter(const VectorWriter &other);
    VectorWriter &operator=(const VectorWriter &other);

    VectorWriter(VectorWriter &&other) noexcept;
    VectorWriter &operator=(VectorWriter &&other) noexcept;

    int getSize() const;

    int &operator[](int index);
    int operator[](int index) const;

    friend VectorWriter &operator<<(VectorWriter &os, const VectorWriter &newVector);
    friend VectorWriter &operator<<(VectorWriter &os, int newNumber);

    void seek(int index);

    int *contents() const;

    ~VectorWriter();

private:
    int *numbers = nullptr;

    int size = 0;
    int capacity = 0;

    int indexToAdd = 0;

    void copyFrom(const VectorWriter &other);
    void moveFrom(VectorWriter &&other);

    void resize();
    void free();

    void addElement(int newNumber);

    void shift();
};