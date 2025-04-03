#include "Book.h"

Book::Book(const char *title, const char *name, const char *iban)
{
    setTitle(title);
    setName(name);
    setIban(iban);
    setCount(1);
}

bool Book::isValidTitle(const char *title) const
{
    return strlen(title) <= BookConstants::MAX_TITLE_LENGTH;
}

bool Book::isValidName(const char *name) const
{
    return strlen(name) <= BookConstants::MAX_NAME_LENGTH;
}

bool Book::isValidIban(const char *iban) const
{
    return strlen(iban) == BookConstants::IBAN_LENGTH;
}

void Book::setTitle(const char *newTitle)
{
    if (isValidTitle(newTitle))
    {
        strcpy(title, newTitle);
    }
}

void Book::setName(const char *newName)
{
    if (isValidName(newName))
    {
        strcpy(name, newName);
    }
}

void Book::setIban(const char *newIban)
{
    if (isValidIban(newIban))
    {
        strcpy(iban, newIban);
    }
}

void Book::setCount(int newCount)
{
    count = newCount;
}

const char *Book::getTitle() const
{
    return title;
}

const char *Book::getName() const
{
    return name;
}

const char *Book::getIban() const
{
    return iban;
}

int Book::getCount() const
{
    return count;
}

void Book::print(std::ofstream &fout) const
{
    fout << getTitle() << ", " << getName() << ", " << getIban() << ", " << getCount() << std::endl;
}