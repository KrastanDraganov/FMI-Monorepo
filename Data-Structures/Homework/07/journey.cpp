#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct State
{
    int line;
    long long cost;
    int trams;
};

struct CompareState
{
    bool operator()(const State &first, const State &second) const
    {
        if (first.cost != second.cost)
        {
            return first.cost > second.cost;
        }

        return first.trams > second.trams;
    }
};

bool isBetter(long long newCost, int newTrams, long long oldCost, int oldTrams)
{
    if (newCost != oldCost)
    {
        return newCost < oldCost;
    }

    return newTrams < oldTrams;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> lineType(k + 1);
    for (int i = 1; i <= k; ++i)
    {
        cin >> lineType[i];
    }

    vector<long long> lineCost(k + 1);
    for (int i = 1; i <= k; ++i)
    {
        cin >> lineCost[i];
    }

    vector<vector<int>> stopToLines(n + 1);
    vector<vector<int>> lineToStops(k + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, t;
        cin >> u >> v >> t;

        stopToLines[u].push_back(t);
        stopToLines[v].push_back(t);

        lineToStops[t].push_back(u);
        lineToStops[t].push_back(v);
    }

    vector<long long> distCost(k + 1, LLONG_MAX);
    vector<int> distTrams(k + 1, INT_MAX);

    priority_queue<State, vector<State>, CompareState> pq;

    for (int i = 0; i < (int)stopToLines[1].size(); ++i)
    {
        int line = stopToLines[1][i];

        long long newCost = lineCost[line];
        int newTrams = lineType[line];

        if (isBetter(newCost, newTrams, distCost[line], distTrams[line]))
        {
            distCost[line] = newCost;
            distTrams[line] = newTrams;

            pq.push({line, newCost, newTrams});
        }
    }

    vector<bool> usedStop(n + 1, false);

    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();

        if (current.cost != distCost[current.line] ||
            current.trams != distTrams[current.line])
        {
            continue;
        }

        for (int i = 0; i < (int)lineToStops[current.line].size(); ++i)
        {
            int stop = lineToStops[current.line][i];

            if (usedStop[stop])
            {
                continue;
            }

            usedStop[stop] = true;

            for (int j = 0; j < (int)stopToLines[stop].size(); ++j)
            {
                int nextLine = stopToLines[stop][j];

                long long newCost = current.cost + lineCost[nextLine];
                int newTrams = current.trams + lineType[nextLine];

                if (isBetter(newCost, newTrams, distCost[nextLine], distTrams[nextLine]))
                {
                    distCost[nextLine] = newCost;
                    distTrams[nextLine] = newTrams;

                    pq.push({nextLine, newCost, newTrams});
                }
            }
        }
    }

    long long answerCost = LLONG_MAX;
    int answerTrams = INT_MAX;

    for (int i = 0; i < (int)stopToLines[n].size(); ++i)
    {
        int line = stopToLines[n][i];

        if (isBetter(distCost[line], distTrams[line], answerCost, answerTrams))
        {
            answerCost = distCost[line];
            answerTrams = distTrams[line];
        }
    }

    cout << answerCost << " " << answerTrams << '\n';

    return 0;
}