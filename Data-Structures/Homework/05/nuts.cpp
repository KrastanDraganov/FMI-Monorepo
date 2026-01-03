#include <iostream>
#include <unordered_map>

void solve()
{
    int x, n;
    std::cin >> x >> n;

    std::unordered_map<int, int> weightToIndexMap;
    std::pair<int, int> result = {-1, -1};

    for (int i = 1; i <= n; ++i)
    {
        int weight;
        std::cin >> weight;

        int target = x - weight;

        if (weightToIndexMap.count(target) > 0)
        {
            result = {weightToIndexMap[target], i};
        }

        weightToIndexMap[weight] = i;
    }

    std::cout << result.first << " " << result.second << "\n";
}

int main()
{
    int tests;
    std::cin >> tests;

    for (int test = 0; test < tests; ++test)
    {
        solve();
    }

    return 0;
}