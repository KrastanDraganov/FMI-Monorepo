#ifndef _LINKED_LIST_HPP
#define _LINKED_LIST_HPP

template <typename T>
struct LinkedListElement
{
    T data;
    LinkedListElement<T> *next;
};

template <typename T>
class LinkedList;

template <typename T>
class LinkedListIterator
{
    using LLE = LinkedListElement<T>;
    using I = LinkedListIterator<T>;

    friend LinkedList<T>;

    LLE *ptr;

public:
    LinkedListIterator(LLE *pos = nullptr) : ptr(pos) {}

    I next() const
    {
        if (!valid())
        {
            return *this;
        }
        return I(ptr->next);
    }

    bool valid() const
    {
        return ptr != nullptr;
    }

    T const &getConst() const
    {
        return ptr->data;
    }

    T &get() const
    {
        return ptr->data;
    }

    operator bool() const
    {
        return valid();
    }

    I &operator++()
    {
        return (*this = next());
    }

    I operator++(int)
    {
        I saved = *this;
        ++(*this);
        return saved;
    }

    T &operator*()
    {
        return get();
    }

    T const &operator*() const
    {
        return getConst();
    }

    bool operator==(I const &it) const
    {
        return ptr == it.ptr;
    }

    bool operator!=(I const &it) const
    {
        return !(*this == it);
    }
};

template <typename T>
class LinkedList
{
public:
    using I = LinkedListIterator<T>;
    using Type = T;

private:
    using LLE = LinkedListElement<T>;

    LLE *front, *back;

public:
    LinkedList() : front(nullptr), back(nullptr) {}

    int insertAfterNInterval(const I &pivotIt, int n, const T &x)
    {
        if (!front)
        {
            return 0;
        }

        LLE *currentElement = front;
        auto currentIt = I(front);

        int positionCounter = -1;
        bool foundPivotIt = false;

        int addedElements = 0;

        while (currentElement)
        {
            if (foundPivotIt)
            {
                ++positionCounter;
            }
            else if (currentIt == pivotIt)
            {
                foundPivotIt = true;
                positionCounter = n;
            }

            if (positionCounter == n)
            {
                LLE *newElement = new LLE(x);

                newElement->next = currentElement->next;
                currentElement->next = newElement;

                ++addedElements;
                positionCounter = 0;

                currentElement = currentElement->next;
                ++currentIt;
            }

            currentElement = currentElement->next;
            ++currentIt;
        }

        return addedElements;
    }
};

#endif