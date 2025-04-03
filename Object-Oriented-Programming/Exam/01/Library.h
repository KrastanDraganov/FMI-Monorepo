#pragma once

#include "Book.h"

namespace LibraryConstants
{
    constexpr int NO_BOOK_FOUND = -1;
}

class Library
{
private:
    int capacity = 0;
    int uniqueBooksCount = 0;

    Book *books = nullptr;

    void copyFrom(const Library &other);
    void free();

    void resize();

    int findBookByIban(const char *targetIban) const;

    void addNewUniqueBook(const Book &newBook);

public:
    Library() = default;

    Library(int maxUniqueBooks);

    Library(const Library &other);
    Library &operator=(const Library &other);
    ~Library();

    void setCapacity(int capacity);

    Library &addBook(Book newBook, int copies);

    int countBooks() const;

    void serialize(std::ofstream fout) const;
    void serialize(std::ofstream fout, bool (*predicate)(const Book &target)) const;

    Library &merge(const Library &other);
};