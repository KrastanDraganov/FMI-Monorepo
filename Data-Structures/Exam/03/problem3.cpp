#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

template <typename T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T> *left, *right;

    BinTreeNode(T data, BinTreeNode<T> *left, BinTreeNode<T> *right) : data(data), left(left), right(right) {}
};

template <typename T>
T traverseCurrentLevelAndFindSum(std::queue<BinTreeNode<T> *> &bfs)
{
    T currentLevelSum;
    bool isSumInitialized = false;

    int currentLevelSize = (int)bfs.size();

    for (int i = 0; i < currentLevelSize; ++i)
    {
        BinTreeNode<T> *currentNode = bfs.front();
        bfs.pop();

        if (isSumInitialized)
        {
            currentLevelSum += currentNode->data;
        }
        else
        {
            currentLevelSum = currentNode->data;
            isSumInitialized = true;
        }

        if (currentNode->left)
        {
            bfs.push(currentNode->left);
        }

        if (currentNode->right)
        {
            bfs.push(currentNode->right);
        }
    }

    return currentLevelSum;
}

template <typename T>
std::vector<int> findTwoLevelsWithSameSum(BinTreeNode<T> *root)
{
    if (!root)
    {
        return {};
    }

    std::vector<int> result;

    std::unordered_map<T, int> levelSumToLevelNumberMap;

    std::queue<BinTreeNode<T> *> bfs;
    bfs.push(root);

    for (int currentLevelNumber = 0; !bfs.empty(); ++currentLevelNumber)
    {
        T currentLevelSum = traverseCurrentLevelAndFindSum(bfs);

        bool foundLevelWithSameSum = levelSumToLevelNumberMap.count(currentLevelSum) > 0;

        if (foundLevelWithSameSum)
        {
            int matchingLevelNumber = levelSumToLevelNumberMap[currentLevelSum];

            result.push_back(matchingLevelNumber);
            result.push_back(currentLevelNumber);

            break;
        }

        levelSumToLevelNumberMap[currentLevelSum] = currentLevelNumber;
    }

    return result;
}

template <typename T>
void freeTree(BinTreeNode<T> *node)
{
    if (!node)
    {
        return;
    }

    if (node->left)
    {
        freeTree(node->left);
    }

    if (node->right)
    {
        freeTree(node->right);
    }

    delete node;
}

int main()
{
    BinTreeNode<int> *root = new BinTreeNode<int>(7,
                                                  new BinTreeNode<int>(4,
                                                                       new BinTreeNode<int>(1, nullptr, nullptr),
                                                                       new BinTreeNode<int>(5, nullptr, nullptr)),
                                                  new BinTreeNode<int>(10,
                                                                       new BinTreeNode<int>(8, nullptr, nullptr),
                                                                       nullptr));

    std::vector<int> result = findTwoLevelsWithSameSum(root);

    if ((int)result.size() != 2)
    {
        std::cout << "There aren't two levels with the same sum!\n";
    }
    else
    {
        std::cout << "There are two levels with the same sum - levels " << result[0] << " and " << result[1] << "\n";
    }

    freeTree(root);

    return 0;
}