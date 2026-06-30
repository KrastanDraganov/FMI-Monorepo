#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<int> numbers(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> numbers[i];
    }

    vector<int> lis;
    vector<int> increasing(n), decreasing(n);

    for (int i = 0; i < n; ++i)
    {
        auto it = lower_bound(lis.begin(), lis.end(), numbers[i]);

        if (it == lis.end())
        {
            lis.push_back(numbers[i]);
            increasing[i] = lis.size();
        }
        else
        {
            *it = numbers[i];
            increasing[i] = it - lis.begin() + 1;
        }
    }

    lis.clear();

    for (int i = n - 1; i >= 0; --i)
    {
        auto it = lower_bound(lis.begin(), lis.end(), numbers[i]);

        if (it == lis.end())
        {
            lis.push_back(numbers[i]);
            decreasing[i] = lis.size();
        }
        else
        {
            *it = numbers[i];
            decreasing[i] = it - lis.begin() + 1;
        }
    }

    int result = 0;

    for (int i = 0; i < n; ++i)
    {
        result = max(result, increasing[i] + decreasing[i] - 1);
    }

    cout << result << endl;

    return 0;
}