#include <iostream>

template <typename T>
struct DCLE
{
    T inf;
    DCLE<T> *next;
    DCLE<T> *prev;

    DCLE(T inf) : inf(inf), next(nullptr), prev(nullptr) {}
};

template <typename T>
DCLE<T> *removeSpecialNodes(DCLE<T> *startNode)
{
    if (!startNode)
    {
        return nullptr;
    }

    DCLE<T> *pivotNode = startNode;
    DCLE<T> **traversalNode = &startNode;

    bool skipPivotCheck = true;

    while (skipPivotCheck || *traversalNode != pivotNode)
    {
        if (skipPivotCheck)
        {
            skipPivotCheck = false;
        }

        DCLE<T> *currentNode = *traversalNode;

        DCLE<T> *nextNode = currentNode->next;
        DCLE<T> *previousNode = currentNode->prev;

        if (currentNode == nextNode || currentNode == previousNode || !nextNode || !previousNode)
        {
            break;
        }

        T sumOfNeighbors = nextNode->inf + previousNode->inf;

        if (sumOfNeighbors == currentNode->inf)
        {
            previousNode->next = nextNode;
            nextNode->prev = previousNode;

            delete currentNode;

            pivotNode = nextNode;
            skipPivotCheck = true;
        }

        *traversalNode = nextNode;
    }

    return pivotNode;
}

template <typename T>
void printList(DCLE<T> *startNode)
{
    if (!startNode)
    {
        return;
    }

    DCLE<T> *traversalNode = startNode;

    do
    {
        std::cout << traversalNode->inf << " ";

        traversalNode = traversalNode->next;
    } while (traversalNode != startNode);
}

template <typename T>
void freeList(DCLE<T> *startNode)
{
    if (!startNode)
    {
        return;
    }

    DCLE<T> *pivotNode = startNode;
    DCLE<T> **traversalNode = &startNode;

    do
    {
        DCLE<T> *currentNode = *traversalNode;
        DCLE<T> *nextNode = currentNode->next;

        delete currentNode;

        *traversalNode = nextNode;
    } while (*traversalNode != pivotNode);
}

int main()
{
    DCLE<unsigned> *node1 = new DCLE<unsigned>(1);
    DCLE<unsigned> *node2 = new DCLE<unsigned>(2);
    DCLE<unsigned> *node3 = new DCLE<unsigned>(3);
    DCLE<unsigned> *node4 = new DCLE<unsigned>(4);
    DCLE<unsigned> *node5 = new DCLE<unsigned>(5);
    DCLE<unsigned> *node7 = new DCLE<unsigned>(7);

    node1->prev = node3;
    node1->next = node7;

    node7->prev = node1;
    node7->next = node4;

    node4->prev = node7;
    node4->next = node2;

    node2->prev = node4;
    node2->next = node5;

    node5->prev = node2;
    node5->next = node3;

    node3->prev = node5;
    node3->next = node1;

    std::cout << "Before: ";
    printList(node5);
    std::cout << "\n";

    DCLE<unsigned> *resultNode = removeSpecialNodes(node5);

    std::cout << "After: ";
    printList(resultNode);
    std::cout << "\n";

    freeList(resultNode);

    return 0;
}