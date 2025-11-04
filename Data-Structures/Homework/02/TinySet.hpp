#pragma once

#include <iostream>

namespace TinySetConstants
{
    constexpr int MAX_CAPACITY = 256;
}

class TinySet
{
public:
    TinySet() : _size(0) {}

    bool add(int x)
    {
        int *pos = lower_bound(x);

        if (pos != end() && *pos == x)
        {
            return false;
        }

        if (_size >= TinySetConstants::MAX_CAPACITY)
        {
            return false;
        }

        for (int *it = _data + _size; it != pos; --it)
        {
            *it = *(it - 1);
        }

        *pos = x;
        ++_size;

        return true;
    }

    bool removeIfExists(int x)
    {
        int *pos = lower_bound(x);

        if (pos == end() || *pos != x)
        {
            return false;
        }

        for (int *it = pos; it + 1 != _data + _size; ++it)
        {
            *it = *(it + 1);
        }

        --_size;

        return true;
    }

    bool contains(int x) const
    {
        const int *pos = lower_bound(x);

        return pos != cend() && *pos == x;
    }

    std::size_t size() const
    {
        return _size;
    }

    bool empty() const
    {
        return _size == 0;
    }

    std::size_t capacity() const
    {
        return TinySetConstants::MAX_CAPACITY;
    }

    class ReverseIterator
    {
    public:
        ReverseIterator(int *ptr) : _ptr(ptr) {}

        int &operator*()
        {
            return *_ptr;
        }

        const int &operator*() const
        {
            return *_ptr;
        }

        ReverseIterator &operator++()
        {
            --_ptr;

            return *this;
        }

        ReverseIterator operator++(int)
        {
            ReverseIterator tmp(*this);
            --_ptr;

            return tmp;
        }

        ReverseIterator &operator--()
        {
            ++_ptr;

            return *this;
        }

        ReverseIterator operator--(int)
        {
            ReverseIterator tmp(*this);
            ++_ptr;

            return tmp;
        }

        bool operator!=(const ReverseIterator &other) const
        {
            return _ptr != other._ptr;
        }

        bool operator==(const ReverseIterator &other) const
        {
            return _ptr == other._ptr;
        }

    private:
        int *_ptr;
    };

    class ConstReverseIterator
    {
    public:
        ConstReverseIterator(const int *ptr) : _ptr(ptr) {}

        const int &operator*() const
        {
            return *_ptr;
        }

        ConstReverseIterator &operator++()
        {
            --_ptr;

            return *this;
        }
        ConstReverseIterator operator++(int)
        {
            ConstReverseIterator tmp(*this);
            --_ptr;

            return tmp;
        }

        ConstReverseIterator &operator--()
        {
            ++_ptr;

            return *this;
        }

        ConstReverseIterator operator--(int)
        {
            ConstReverseIterator tmp(*this);
            ++_ptr;

            return tmp;
        }

        bool operator!=(const ConstReverseIterator &other) const
        {
            return _ptr != other._ptr;
        }

        bool operator==(const ConstReverseIterator &other) const
        {
            return _ptr == other._ptr;
        }

    private:
        const int *_ptr;
    };

    using iterator = int *;
    using const_iterator = const int *;
    using reverse_iterator = ReverseIterator;
    using const_reverse_iterator = ConstReverseIterator;

    iterator begin()
    {
        return _data;
    }

    iterator end()
    {
        return _data + _size;
    }

    const_iterator begin() const
    {
        return _data;
    }

    const_iterator end() const
    {
        return _data + _size;
    }

    const_iterator cbegin() const
    {
        return _data;
    }

    const_iterator cend() const
    {
        return _data + _size;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(_data + _size - 1);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(_data - 1);
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(_data + _size - 1);
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(_data - 1);
    }

private:
    int *lower_bound(int x)
    {
        std::size_t left = 0;
        std::size_t right = _size;

        while (left < right)
        {
            std::size_t mid = (left + right) / 2;

            if (_data[mid] < x)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }

        return (_data + left);
    }

    const int *lower_bound(int x) const
    {
        std::size_t left = 0;
        std::size_t right = _size;

        while (left < right)
        {
            std::size_t mid = (left + right) / 2;

            if (_data[mid] < x)
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }

        return (_data + left);
    }

    int _data[TinySetConstants::MAX_CAPACITY];

    std::size_t _size;
};
