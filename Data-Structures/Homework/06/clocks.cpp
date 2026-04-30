#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define endl '\n'

using namespace std;

void addInterval(vector<pair<long long, int>> &events, long long start, long long end)
{
    events.push_back({start, 1});
    events.push_back({end + 1, -1});
}

long long getActiveIntervals(long long time, vector<pair<long long, long long>> &prefixEvents)
{
    auto it = upper_bound(prefixEvents.begin(), prefixEvents.end(), make_pair(time, LLONG_MAX));

    if (it == prefixEvents.begin())
    {
        return 0;
    }

    --it;

    return it->second;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;

    cin >> n >> m;

    vector<pair<long long, int>> events;
    long long fullCyclesSum = 0;

    for (int i = 0; i < n; ++i)
    {
        long long a, b;
        cin >> a >> b;

        fullCyclesSum += a / m;

        long long remainder = a % m;

        if (remainder == 0)
        {
            continue;
        }

        long long end = (b + remainder - 1) % m;

        if (b <= end)
        {
            addInterval(events, b, end);
        }
        else
        {
            addInterval(events, b, m - 1);
            addInterval(events, 0, end);
        }
    }

    sort(events.begin(), events.end());

    vector<pair<long long, long long>> prefixEvents;

    int i = 0;
    long long current = 0;

    while (i < events.size())
    {
        long long position = events[i].first;
        long long delta = 0;

        while (i < events.size() && events[i].first == position)
        {
            delta += events[i].second;
            ++i;
        }

        current += delta;
        prefixEvents.push_back({position, current});
    }

    int q;
    cin >> q;

    while (q--)
    {
        long long time;
        cin >> time;

        cout << fullCyclesSum + getActiveIntervals(time, prefixEvents) << endl;
    }

    return 0;
}