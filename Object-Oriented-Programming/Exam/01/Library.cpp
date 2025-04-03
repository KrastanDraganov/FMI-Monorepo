#include "Library.h"

void Library::copyFrom(const Library &other)
{
    capacity = other.capacity;
    uniqueBooksCount = other.uniqueBooksCount;

    books = new Book[capacity];

    for (int i = 0; i < uniqueBooksCount; ++i)
    {
        books[i] = other.books[i];
    }
}

void Library::free()
{
    if (books != nullptr)
    {
        delete[] books;
        books = nullptr;
    }

    capacity = 0;
    uniqueBooksCount = 0;
}

void Library::resize()
{
    capacity *= 2;

    Book *newBooks = new Book[capacity];

    for (int i = 0; i < uniqueBooksCount; ++i)
    {
        newBooks[i] = books[i];
    }

    delete[] books;
    books = newBooks;
}

Library::Library(int maxUniqueBooks)
{
    setCapacity(maxUniqueBooks);

    books = new Book[capacity];
}

Library::Library(const Library &other)
{
    copyFrom(other);
}

Library &Library::operator=(const Library &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Library::~Library()
{
    free();
}

void Library::setCapacity(int newCapacity)
{
    capacity = newCapacity;
}

int Library::findBookByIban(const char *targetIban) const
{
    for (int i = 0; i < uniqueBooksCount; ++i)
    {
        if (strcmp(books[i].getIban(), targetIban) == 0)
        {
            return i;
        }
    }

    return LibraryConstants::NO_BOOK_FOUND;
}

void Library::addNewUniqueBook(const Book &newBook)
{
    if (uniqueBooksCount == capacity)
    {
        resize();
    }

    books[uniqueBooksCount] = newBook;
    ++uniqueBooksCount;
}

Library &Library::addBook(Book newBook, int copies)
{
    int bookIndexInCurrentLibrary = findBookByIban(newBook.getIban());

    if (bookIndexInCurrentLibrary == LibraryConstants::NO_BOOK_FOUND)
    {
        newBook.setCount(copies);
        addNewUniqueBook(newBook);
    }
    else
    {
        int newCount = books[bookIndexInCurrentLibrary].getCount() + copies;
        books[bookIndexInCurrentLibrary].setCount(newCount);
    }

    return *this;
}

int Library::countBooks() const
{
    int result = 0;

    for (int i = 0; i < uniqueBooksCount; ++i)
    {
        result += books[i].getCount();
    }

    return result;
}

void Library::serialize(std::ofstream fout) const
{
    for (int i = 0; i < uniqueBooksCount; ++i)
    {
        books[i].print(fout);
    }
}

void Library::serialize(std::ofstream fout, bool (*predicate)(const Book &target)) const
{
    for (int i = 0; i < uniqueBooksCount; ++i)
    {
        if (predicate(books[i]))
        {
            books[i].print(fout);
        }
    }
}

Library &Library::merge(const Library &other)
{
    int newPotentialCount = uniqueBooksCount + other.uniqueBooksCount;

    while (capacity < newPotentialCount)
    {
        resize();
    }

    for (int i = 0; i < other.uniqueBooksCount; ++i)
    {
        addBook(other.books[i], other.books[i].getCount());
    }

    return *this;
}
