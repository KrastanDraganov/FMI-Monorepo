#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define endl '\n'

using namespace std;

long long getIntervalStart(long long length, int n, const vector<long long> &l, const vector<long long> &r)
{
    int i = 0, j = 0;
    long long result = 0;

    for (int k = 0; k < n; ++k)
    {
        long long startL = (i < n ? l[i] : LLONG_MAX);
        long long startR = (j < n ? r[j] - length + 1 : LLONG_MAX);

        if (startL <= startR)
        {
            result = startL;
            ++i;
        }
        else
        {
            result = startR;
            ++j;
        }
    }

    return result;
}

bool check(long long length, int n, vector<long long> &l, vector<long long> &r, vector<long long> &prefixL, vector<long long> &prefixR, long long k)
{
    if (length == 0)
    {
        return true;
    }

    long long start = getIntervalStart(length, n, l, r);
    int leftCount = upper_bound(r.begin(), r.end(), start + length - 2) - r.begin();

    long long cost = start * leftCount - (prefixR[leftCount] - 1ll * leftCount * (length - 1));

    if (cost > k)
    {
        return false;
    }

    int rightCountStart = upper_bound(l.begin(), l.end(), start) - l.begin();

    cost += (prefixL[n] - prefixL[rightCountStart]) - start * (n - rightCountStart);

    return cost <= k;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> l(n), r(n);
    long long minimumLength = -1;

    for (int i = 0; i < n; ++i)
    {
        cin >> l[i] >> r[i];

        if (minimumLength == -1 || r[i] - l[i] + 1 < minimumLength)
        {
            minimumLength = r[i] - l[i] + 1;
        }
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    vector<long long> prefixL(n + 1), prefixR(n + 1);

    for (int i = 0; i < n; ++i)
    {
        prefixL[i + 1] = prefixL[i] + l[i];
        prefixR[i + 1] = prefixR[i] + r[i];
    }

    long long left = 0, right = minimumLength;

    while (left <= right)
    {
        long long mid = (left + right) / 2;

        if (check(mid, n, l, r, prefixL, prefixR, k))
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    cout << left - 1 << endl;

    return 0;
}