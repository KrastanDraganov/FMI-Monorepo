#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>

namespace LRUCacheConstants
{
    constexpr int NO_VALUE = -1;
}

class LRUCache
{
public:
    LRUCache(int capacity) : capacity(capacity), uniqueElements(0) {}

    int get(int key)
    {
        if (!contains(key))
        {
            return LRUCacheConstants::NO_VALUE;
        }

        history.push_back(key);
        ++visitedAfterCreationCounter[key];

        return values[key];
    }

    void put(int key, int newValue)
    {
        if (!contains(key))
        {
            ++uniqueElements;
        }
        else
        {
            ++visitedAfterCreationCounter[key];
        }

        if (uniqueElements > capacity)
        {
            deleteOldestUsedElement();
        }

        values[key] = newValue;
        history.push_back(key);
    }

    void deleteOldestUsedElement()
    {
        if (history.empty())
        {
            return;
        }

        while (visitedAfterCreationCounter[history.front()] > 0)
        {
            --visitedAfterCreationCounter[history.front()];
            history.pop_front();
        }

        values[history.front()] = LRUCacheConstants::NO_VALUE;
        history.pop_front();

        --uniqueElements;
    }

private:
    int capacity;
    int uniqueElements;

    std::unordered_map<int, int> values, visitedAfterCreationCounter;
    std::deque<int> history;

    bool contains(int key)
    {
        return values.count(key) > 0 && values[key] != LRUCacheConstants::NO_VALUE;
    }
};

int main()
{
    int n, q, k;
    std::cin >> n >> q >> k;

    LRUCache cache(n);

    for (int query = 0; query < q; ++query)
    {
        std::string operation;
        int target;
        std::cin >> operation >> target;

        if (operation == "get")
        {
            std::cout << cache.get(target) << "\n";
        }
        else
        {
            int newValue;
            std::cin >> newValue;

            cache.put(target, newValue);
        }

        if ((query + 1) % k == 0)
        {
            cache.deleteOldestUsedElement();
        }
    }

    return 0;
}
