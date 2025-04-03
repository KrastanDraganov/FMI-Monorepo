#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

namespace BookConstants
{
    constexpr int MAX_TITLE_LENGTH = 100;
    constexpr int MAX_NAME_LENGTH = 50;
    constexpr int IBAN_LENGTH = 10;
}

class Book
{
private:
    char title[BookConstants::MAX_TITLE_LENGTH + 1] = "";
    char name[BookConstants::MAX_NAME_LENGTH + 1] = "";
    char iban[BookConstants::IBAN_LENGTH + 1] = "";

    // New field for subtask 2 with Library in order to
    // track the number of same books in the library
    int count = 0;

    bool isValidTitle(const char *title) const;
    bool isValidName(const char *name) const;
    bool isValidIban(const char *iban) const;

public:
    Book() = default;

    Book(const char *title, const char *name, const char *iban);

    void setTitle(const char *newTitle);
    void setName(const char *newName);
    void setIban(const char *newIban);
    void setCount(int newCount);

    const char *getTitle() const;
    const char *getName() const;
    const char *getIban() const;
    int getCount() const;

    void print(std::ofstream &fout) const;
};