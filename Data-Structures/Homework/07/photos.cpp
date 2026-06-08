#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

struct State
{
    int row;
    int col;
    int value;
};

struct CompareState
{
    bool operator()(const State &first, const State &second) const
    {
        return first.value < second.value;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);

    int startRow = -1, startCol = -1;
    int endRow = -1, endCol = -1;

    queue<pair<int, int>> bfsQueue;
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

    for (int row = 0; row < n; ++row)
    {
        cin >> grid[row];

        for (int col = 0; col < m; ++col)
        {
            if (grid[row][col] == '+')
            {
                dist[row][col] = 0;
                bfsQueue.push({row, col});
            }
            else if (grid[row][col] == 'P')
            {
                startRow = row;
                startCol = col;
            }
            else if (grid[row][col] == 'C')
            {
                endRow = row;
                endCol = col;
            }
        }
    }

    const int dRow[] = {-1, 1, 0, 0};
    const int dCol[] = {0, 0, -1, 1};

    while (!bfsQueue.empty())
    {
        pair<int, int> current = bfsQueue.front();
        bfsQueue.pop();

        int row = current.first;
        int col = current.second;

        for (int dir = 0; dir < 4; ++dir)
        {
            int nextRow = row + dRow[dir];
            int nextCol = col + dCol[dir];

            if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m)
            {
                continue;
            }

            if (dist[nextRow][nextCol] != INT_MAX)
            {
                continue;
            }

            dist[nextRow][nextCol] = dist[row][col] + 1;
            bfsQueue.push({nextRow, nextCol});
        }
    }

    vector<vector<int>> best(n, vector<int>(m, -1));
    best[startRow][startCol] = dist[startRow][startCol];

    priority_queue<State, vector<State>, CompareState> dijkstra;
    dijkstra.push({startRow, startCol, dist[startRow][startCol]});

    while (!dijkstra.empty())
    {
        State current = dijkstra.top();
        dijkstra.pop();

        if (current.value != best[current.row][current.col])
        {
            continue;
        }

        if (current.row == endRow && current.col == endCol)
        {
            cout << current.value << '\n';

            return 0;
        }

        for (int dir = 0; dir < 4; ++dir)
        {
            int nextRow = current.row + dRow[dir];
            int nextCol = current.col + dCol[dir];

            if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m)
            {
                continue;
            }

            int newValue = min(current.value, dist[nextRow][nextCol]);

            if (newValue > best[nextRow][nextCol])
            {
                best[nextRow][nextCol] = newValue;

                dijkstra.push({nextRow, nextCol, newValue});
            }
        }
    }

    return 0;
}