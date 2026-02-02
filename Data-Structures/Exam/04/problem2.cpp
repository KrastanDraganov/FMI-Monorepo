#include <iostream>
#include <vector>

class Graph
{
public:
    Graph(int nodesCount) : nodesCount(nodesCount)
    {
        edges.resize(nodesCount);
    }

    void addEdge(int from, int to)
    {
        edges[from].push_back(to);
        edges[to].push_back(from);
    }

    bool canGoBack(int startNode, int directionNode)
    {
        if (!edgeExists(startNode, directionNode))
        {
            return false;
        }

        std::vector<bool> visited(nodesCount, false);
        visited[startNode] = true;

        return dfs(directionNode, startNode, directionNode, visited);
    }

private:
    int nodesCount;
    std::vector<std::vector<int>> edges;

    bool edgeExists(int startNode, int endNode)
    {
        for (int currentNode : edges[startNode])
        {
            if (currentNode == endNode)
            {
                return true;
            }
        }

        return false;
    }

    bool dfs(int currentNode, int homeNode, int forbiddenNode, std::vector<bool> &visited)
    {
        visited[currentNode] = true;

        for (int nextNode : edges[currentNode])
        {
            if (!visited[nextNode])
            {
                if (dfs(nextNode, homeNode, forbiddenNode, visited))
                {
                    return true;
                }
            }
            else if (nextNode == homeNode && currentNode != forbiddenNode)
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Graph graph(7);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 5);
    graph.addEdge(0, 6);
    graph.addEdge(4, 6);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    std::cout << "Start from 0 and go (0, 1) -> " << graph.canGoBack(0, 1) << "\n";
    std::cout << "Start from 0 and go (0, 2) -> " << graph.canGoBack(0, 2) << "\n";
    std::cout << "Start from 0 and go (0, 5) -> " << graph.canGoBack(0, 5) << "\n";
    std::cout << "Start from 0 and go (0, 6) -> " << graph.canGoBack(0, 6) << "\n";

    // Test invalid edge
    std::cout << "Start from 0 and go (0, 3) -> " << graph.canGoBack(0, 3) << "\n";

    std::cout << "Start from 5 and go (5, 0) -> " << graph.canGoBack(5, 0) << "\n";
    std::cout << "Start from 5 and go (5, 3) -> " << graph.canGoBack(5, 3) << "\n";

    return 0;
}