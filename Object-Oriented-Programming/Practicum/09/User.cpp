#include "User.h"

int User::users = 0;

void User::copyFrom(const User &other)
{
    id = other.id;
    age = other.age;

    size = other.size;
    capacity = other.capacity;

    name = new char[capacity + 1];
    strcpy(name, other.name);
}

void User::moveFrom(User &&other)
{
    id = other.id;
    age = other.age;

    size = other.size;
    capacity = other.capacity;

    name = other.name;
    other.name = nullptr;
}

void User::free()
{
    id = 0;
    age = 1;

    size = 0;
    capacity = 0;

    delete[] name;
    name = nullptr;
}

User::User(const User &other)
{
    copyFrom(other);
}

User::User(User &&other)
{
    moveFrom(std::move(other));
}

User &User::operator=(const User &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

User &User::operator=(User &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

User::~User()
{
    free();
}
