#include <iostream>

struct LinkedListElement
{
    int data;
    LinkedListElement *next;

    LinkedListElement(int data, LinkedListElement *next = nullptr) : data(data), next(next) {}
};

void print(const LinkedListElement *list)
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

void freeList(LinkedListElement *list)
{
    while (list)
    {
        LinkedListElement *toDelete = list;
        list = list->next;

        delete toDelete;
    }
}

void pushBack(LinkedListElement *&head, LinkedListElement *&tail, LinkedListElement *toAdd)
{
    toAdd->next = nullptr;

    if (!head)
    {
        head = tail = toAdd;
    }
    else
    {
        tail->next = toAdd;
        tail = toAdd;
    }
}

void addToResult(LinkedListElement *&newHead, LinkedListElement *&newTail, LinkedListElement *toAddHead, LinkedListElement *toAddTail)
{
    if (!toAddHead)
    {
        return;
    }

    if (!newHead)
    {
        newHead = toAddHead;
        newTail = toAddTail;
    }
    else
    {
        newTail->next = toAddHead;
        newTail = toAddTail;
    }
}

LinkedListElement *rearrange(LinkedListElement *head)
{
    LinkedListElement *remainderOneHead = nullptr, *remainderOneTail = nullptr;
    LinkedListElement *remainderTwoHead = nullptr, *remainderTwoTail = nullptr;

    LinkedListElement **iter = &head;

    while (*iter)
    {
        LinkedListElement *current = *iter;
        LinkedListElement *next = current->next;

        current->next = nullptr;

        int number = current->data;

        if (number % 3 == 1)
        {
            pushBack(remainderOneHead, remainderOneTail, current);
        }
        else if (number % 3 == 2)
        {
            pushBack(remainderTwoHead, remainderTwoTail, current);
        }
        else
        {
            delete current;
        }

        *iter = next;
    }

    LinkedListElement *newHead = nullptr;
    LinkedListElement *newTail = nullptr;

    addToResult(newHead, newTail, remainderOneHead, remainderOneTail);
    addToResult(newHead, newTail, remainderTwoHead, remainderTwoTail);

    if (newTail)
    {
        newTail->next = nullptr;
    }

    return newHead;
}

int main()
{
    LinkedListElement *myList = new LinkedListElement(0,
                                                      new LinkedListElement(1,
                                                                            new LinkedListElement(2,
                                                                                                  new LinkedListElement(3,
                                                                                                                        new LinkedListElement(4,
                                                                                                                                              new LinkedListElement(5,
                                                                                                                                                                    new LinkedListElement(6)))))));

    std::cout << "List before change: ";
    print(myList);

    myList = rearrange(myList);

    std::cout << "List after change: ";
    print(myList);

    freeList(myList);

    return 0;
}