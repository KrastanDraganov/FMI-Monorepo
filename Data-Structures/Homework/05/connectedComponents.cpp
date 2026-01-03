#include <iostream>
#include <vector>

class DSU
{
public:
    DSU(int n)
    {
        parent.resize(n + 1);
        depth.resize(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
            depth[i] = 1;
        }
    }

    bool combine(int x, int y)
    {
        int root1 = findParent(x);
        int root2 = findParent(y);

        if (root1 == root2)
        {
            return false;
        }

        if (depth[root2] > depth[root1])
        {
            std::swap(root1, root2);
        }

        parent[root2] = root1;
        depth[root1] += depth[root2];

        return true;
    }

private:
    std::vector<int> parent;
    std::vector<int> depth;

    int findParent(int x)
    {
        if (x == parent[x])
        {
            return x;
        }

        return parent[x] = findParent(parent[x]);
    }
};

int main()
{
    int n;
    std::cin >> n;

    DSU dsu(n);
    int allComponents = n;

    int x, y;
    while (std::cin >> x >> y)
    {
        bool merged = dsu.combine(x, y);

        if (merged)
        {
            --allComponents;
            std::cout << allComponents << "\n";
        }
        else
        {
            std::cout << allComponents << " CYCLE FORMED!\n";
        }
    }

    return 0;
}