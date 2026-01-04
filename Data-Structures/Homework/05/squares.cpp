#include <iostream>

struct Node
{
    int value;
    Node *next;

    Node(int value, Node *next = nullptr) : value(value), next(next) {};
};

int main()
{
    int n, x, y;
    std::cin >> n >> x >> y;

    Node *head = new Node(-1);
    Node *tail = new Node(-1);

    for (int i = 0; i < n; ++i)
    {
        int value;
        std::cin >> value;

        Node *newNode = new Node(value);

        if (head->next == nullptr)
        {
            head->next = newNode;
        }

        tail->next = newNode;
        tail = tail->next;
    }

    Node *current = head;

    while (current)
    {
        Node *startOfReversal = current;
        Node *endOfReversal = current->next;

        Node *previousNode = current;

        current = current->next;

        for (int i = 0; i < x && current; ++i)
        {
            Node *nextNode = current->next;

            current->next = previousNode;

            previousNode = current;
            current = nextNode;
        }

        startOfReversal->next = previousNode;

        if (endOfReversal)
        {
            endOfReversal->next = current;
        }

        for (int i = 0; i < y - 1 && current; ++i)
        {
            current = current->next;
        }
    }

    head = head->next;

    while (head)
    {
        Node *nextNode = head->next;

        std::cout << head->value << "\n";

        delete head;
        head = nextNode;
    }

    return 0;
}