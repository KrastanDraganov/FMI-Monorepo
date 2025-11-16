#include <iostream>

struct Node
{
    char data;
    Node *next;

    Node(char data, Node *next = nullptr) : data(data), next(next) {}
};

void print(const Node *list)
{
    while (list)
    {
        std::cout << list->data;

        if (list->next)
        {
            std::cout << " -> ";
        }

        list = list->next;
    }

    std::cout << "\n";
}

void freeList(Node *list)
{
    while (list)
    {
        Node *toDelete = list;
        list = list->next;

        delete toDelete;
    }
}

bool isLower(char c)
{
    return c >= 'a' && c <= 'z';
}

bool isUpper(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool isDigitChar(char c)
{
    return c >= '0' && c <= '9';
}

Node *transformList(Node *head)
{
    Node **curr = &head;

    while (*curr)
    {
        Node *node = *curr;
        char c = node->data;

        if (isLower(c))
        {
            Node *upperNode = new Node(c - 'a' + 'A', node);
            *curr = upperNode;

            curr = &(node->next);
        }
        else if (isDigitChar(c))
        {
            node->data = '*';
            curr = &(node->next);
        }
        else if (isUpper(c))
        {
            curr = &(node->next);
        }
        else
        {
            *curr = node->next;
            delete node;
        }
    }

    return head;
}

int main()
{
    Node *input = new Node('a',
                           new Node('b',
                                    new Node('1',
                                             new Node('-',
                                                      new Node('C',
                                                               new Node('@',
                                                                        new Node('z')))))));

    std::cout << "Original: ";
    print(input);

    input = transformList(input);

    std::cout << "Transformed: ";
    print(input);

    freeList(input);

    return 0;
}
