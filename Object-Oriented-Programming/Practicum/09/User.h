#pragma once

#include <cstring>
#include <iostream>

class User
{
public:
    User() = default;

    User(const User &other);
    User &operator=(const User &other);

    User(User &&other) noexcept;
    User &operator=(User &&other) noexcept;

    ~User();

private:
    static int users;

    int id = 0;
    int age = 1;

    int size = 0;
    int capacity = 0;

    char *name = nullptr;

    void copyFrom(const User &other);
    void moveFrom(User &&other);

    void free();
};