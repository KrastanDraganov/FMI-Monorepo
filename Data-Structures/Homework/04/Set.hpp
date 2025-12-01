#pragma once

class Set
{
public:
    ~Set();
    bool contains(int toFind) const;
    bool insert(int toAdd);
    bool remove(int toDelete);

    bool isSubSet(const Set &other) const;
    bool operator==(const Set &other) const;

private:
    struct Node
    {
        Node *left;
        Node *right;
        int data;

        Node(int data, Node *left = nullptr, Node *right = nullptr);
    };

    Node *root = nullptr;

    void free(Node *root);
    Node *copyFrom(const Node *root);

    bool isSubSetHelper(const Node *otherRoot) const;
};

Set::~Set()
{
    free(root);
    root = nullptr;
}

bool Set::contains(int toFind) const
{
    Node *curr = root;

    while (curr)
    {
        if (curr->data == toFind)
        {
            return true;
        }
        else if (toFind < curr->data)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return false;
}

bool Set::insert(int toAdd)
{
    Node **curr = &root;

    while (*curr)
    {
        if ((*curr)->data == toAdd)
        {
            return false;
        }
        else if (toAdd < (*curr)->data)
        {
            curr = &(*curr)->left;
        }
        else
        {
            curr = &(*curr)->right;
        }
    }

    *curr = new Node(toAdd);

    return true;
}

bool Set::remove(int toDelete)
{
    Node **curr = &root;

    while (*curr)
    {
        if ((*curr)->data == toDelete)
        {
            if (!(*curr)->left && !(*curr)->right)
            {
                delete *curr;
                *curr = nullptr;
            }
            else if (!(*curr)->right)
            {
                Node *toDeleteNode = *curr;
                *curr = (*curr)->left;

                delete toDeleteNode;
            }
            else if (!(*curr)->left)
            {
                Node *toDeleteNode = *curr;
                *curr = (*curr)->right;

                delete toDeleteNode;
            }
            else
            {
            }

            return true;
        }
        else if (toDelete < (*curr)->data)
        {
            curr = &(*curr)->left;
        }
        else
        {
            curr = &(*curr)->right;
        }
    }
    return false;
}

Set::Node::Node(int data, Node *left, Node *right) : left(left), right(right), data(data) {}

void Set::free(Node *root)
{
    if (!root)
    {
        return;
    }

    free(root->left);
    free(root->right);

    delete root;
}

Set::Node *Set::copyFrom(const Node *root)
{
    if (!root)
    {
        return nullptr;
    }

    Node *result = new Node(root->data);

    result->left = copyFrom(root->left);
    result->right = copyFrom(root->right);

    return result;
}

bool Set::isSubSetHelper(const Node *otherRoot) const
{
    if (!otherRoot)
    {
        return true;
    }

    if (!contains(otherRoot->data))
    {
        return false;
    }

    if (!isSubSetHelper(otherRoot->left))
    {
        return false;
    }

    if (!isSubSetHelper(otherRoot->right))
    {
        return false;
    }

    return true;
}

bool Set::isSubSet(const Set &other) const
{
    return isSubSetHelper(other.root);
}

bool Set::operator==(const Set &other) const
{
    return this->isSubSet(other) && other.isSubSet(*this);
}
