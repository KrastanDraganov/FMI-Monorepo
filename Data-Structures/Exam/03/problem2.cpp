#include <iostream>
#include <vector>
#include <unordered_map>

namespace GraphConstants
{
    constexpr int NOT_IN_TRAVERSAL_STACK = -1;
}

class Graph
{
public:
    Graph(int allVerticesCount) : allVerticesCount(allVerticesCount)
    {
        neighbors.resize(allVerticesCount);
    }

    void addEdge(int from, int to)
    {
        neighbors[from].push_back(to);
    }

    bool isThereCycleWithFixedLength(int startVertex, int targetCycleLength)
    {
        std::vector<bool> visited(allVerticesCount, false);

        std::unordered_map<int, int> vertexToTraversalStackNumberMap;

        return dfs(startVertex, 0, targetCycleLength, visited, vertexToTraversalStackNumberMap);
    }

private:
    int allVerticesCount;
    std::vector<std::vector<int>> neighbors;

    bool dfs(int currentVertex, int currentTraversalStackNumber, int targetCycleLength, std::vector<bool> &visited, std::unordered_map<int, int> &vertexToTraversalStackNumberMap)
    {
        vertexToTraversalStackNumberMap[currentVertex] = currentTraversalStackNumber;
        visited[currentVertex] = true;

        for (int nextVertex : neighbors[currentVertex])
        {
            bool foundCycle = vertexToTraversalStackNumberMap.count(nextVertex) > 0 && vertexToTraversalStackNumberMap[nextVertex] != GraphConstants::NOT_IN_TRAVERSAL_STACK;

            if (foundCycle)
            {
                int currentCycleLength = currentTraversalStackNumber - vertexToTraversalStackNumberMap[nextVertex] + 1;

                if (currentCycleLength == targetCycleLength)
                {
                    return true;
                }

                continue;
            }

            if (visited[nextVertex])
            {
                continue;
            }

            if (dfs(nextVertex, currentTraversalStackNumber + 1, targetCycleLength, visited, vertexToTraversalStackNumberMap))
            {
                return true;
            }
        }

        vertexToTraversalStackNumberMap[currentVertex] = GraphConstants::NOT_IN_TRAVERSAL_STACK;

        return false;
    }
};

bool isThereSimpleCycle(Graph &graph, int startVertex, int targetCycleLength)
{
    return graph.isThereCycleWithFixedLength(startVertex, targetCycleLength);
}

int main()
{
    Graph graph(6);

    graph.addEdge(1, 4);

    graph.addEdge(4, 5);

    graph.addEdge(5, 0);

    graph.addEdge(0, 2);
    graph.addEdge(0, 4);

    graph.addEdge(2, 4);
    graph.addEdge(2, 3);

    std::cout << isThereSimpleCycle(graph, 1, 3) << "\n";
    std::cout << isThereSimpleCycle(graph, 1, 4) << "\n";
    std::cout << isThereSimpleCycle(graph, 3, 4) << "\n";

    return 0;
}