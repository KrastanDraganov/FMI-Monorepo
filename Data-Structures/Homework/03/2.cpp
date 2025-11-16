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

void pushBack(Node *&begin, Node *&end, Node *toAdd)
{
    toAdd->next = nullptr;

    if (!begin)
    {
        begin = end = toAdd;
    }
    else
    {
        end->next = toAdd;
        end = toAdd;
    }
}

void concatToResult(Node *&newHead, Node *&newTail, Node *b, Node *e)
{
    if (!b)
    {
        return;
    }

    if (!newHead)
    {
        newHead = b;
        newTail = e;
    }
    else
    {
        newTail->next = b;
        newTail = e;
    }
}

template <class Pred>
void rearrangeByPred(Node *list,
                     Pred pred,
                     Node *&leftBegin, Node *&leftEnd,
                     Node *&rightBegin, Node *&rightEnd)
{
    leftBegin = leftEnd = rightBegin = rightEnd = nullptr;

    Node *curr = list;

    while (curr)
    {
        Node *next = curr->next;
        curr->next = nullptr;

        if (pred(curr->data))
        {
            pushBack(leftBegin, leftEnd, curr);
        }
        else
        {
            pushBack(rightBegin, rightEnd, curr);
        }

        curr = next;
    }
}

Node *reorderListWithRearrange(Node *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Node *lowerBegin = nullptr, *lowerEnd = nullptr;
    Node *restBegin = nullptr, *restEnd = nullptr;

    rearrangeByPred(head, isLower, lowerBegin, lowerEnd, restBegin, restEnd);

    Node *upperBegin = nullptr, *upperEnd = nullptr;
    Node *rest2Begin = nullptr, *rest2End = nullptr;

    rearrangeByPred(restBegin, isUpper, upperBegin, upperEnd, rest2Begin, rest2End);

    Node *digitBegin = nullptr, *digitEnd = nullptr;
    Node *otherBegin = nullptr, *otherEnd = nullptr;

    rearrangeByPred(rest2Begin, isDigitChar, digitBegin, digitEnd, otherBegin, otherEnd);

    Node *newHead = nullptr;
    Node *newTail = nullptr;

    concatToResult(newHead, newTail, lowerBegin, lowerEnd);
    concatToResult(newHead, newTail, upperBegin, upperEnd);
    concatToResult(newHead, newTail, digitBegin, digitEnd);
    concatToResult(newHead, newTail, otherBegin, otherEnd);

    if (newTail)
    {
        newTail->next = nullptr;
    }

    return newHead;
}

Node *reorderListWithFourPointers(Node *head)
{
    if (!head || !head->next)
    {
        return head;
    }

    Node *lowerHead = nullptr, *lowerTail = nullptr;
    Node *upperHead = nullptr, *upperTail = nullptr;
    Node *digitHead = nullptr, *digitTail = nullptr;
    Node *otherHead = nullptr, *otherTail = nullptr;

    Node *curr = head;
    while (curr)
    {
        Node *next = curr->next;
        curr->next = nullptr;

        char c = curr->data;

        if (isLower(c))
        {
            pushBack(lowerHead, lowerTail, curr);
        }
        else if (isUpper(c))
        {
            pushBack(upperHead, upperTail, curr);
        }
        else if (isDigitChar(c))
        {
            pushBack(digitHead, digitTail, curr);
        }
        else
        {
            pushBack(otherHead, otherTail, curr);
        }

        curr = next;
    }

    Node *newHead = nullptr;
    Node *newTail = nullptr;

    concatToResult(newHead, newTail, lowerHead, lowerTail);
    concatToResult(newHead, newTail, upperHead, upperTail);
    concatToResult(newHead, newTail, digitHead, digitTail);
    concatToResult(newHead, newTail, otherHead, otherTail);

    if (newTail)
    {
        newTail->next = nullptr;
    }

    return newHead;
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

    input = reorderListWithRearrange(input);

    std::cout << "Reordered: ";
    print(input);

    freeList(input);
    std::cout << "\n";

    return 0;
}
