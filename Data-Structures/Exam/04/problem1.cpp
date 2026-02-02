#include <iostream>

namespace NodeTypes
{
    constexpr int NOT_LEAF = 0;
    constexpr int NORMAL_LEAF = 1;
    constexpr int BIG_LEAF = 2;
};

template <typename T>
struct TNode
{
    T data;

    TNode<T> *left;
    TNode<T> *right;

    TNode(T data) : data(data), left(nullptr), right(nullptr) {}

    TNode(T data, TNode<T> *left, TNode<T> *right) : data(data), left(left), right(right) {}
};

template <typename T>
int getNodeType(TNode<T> *node)
{
    if (!node)
    {
        return NodeTypes::NOT_LEAF;
    }

    if (!node->left && !node->right)
    {
        return NodeTypes::NORMAL_LEAF;
    }

    if (!node->left && node->right && getNodeType(node->right) == NodeTypes::NORMAL_LEAF)
    {
        return NodeTypes::BIG_LEAF;
    }

    if (node->left && !node->right && getNodeType(node->left) == NodeTypes::NORMAL_LEAF)
    {
        return NodeTypes::BIG_LEAF;
    }

    return NodeTypes::NOT_LEAF;
}

template <typename T>
TNode<T> *removeBigLeaves(TNode<T> *root)
{
    if (!root)
    {
        return nullptr;
    }

    if (getNodeType(root) == NodeTypes::BIG_LEAF)
    {
        if (root->left)
        {
            delete root->left;
        }

        if (root->right)
        {
            delete root->right;
        }

        delete root;

        return nullptr;
    }

    root->left = removeBigLeaves(root->left);
    root->right = removeBigLeaves(root->right);

    return root;
}

template <typename T>
void printTree(TNode<T> *root)
{
    if (!root)
    {
        return;
    }

    std::cout << "Current node " << root->data << " -> ";
    std::cout << (root->left ? root->left->data : -1) << " and ";
    std::cout << (root->right ? root->right->data : -1) << "\n";

    printTree(root->left);
    printTree(root->right);
}

template <typename T>
void freeTree(TNode<T> *root)
{
    if (!root)
    {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

int main()
{
    TNode<int> *root = new TNode<int>(1,
                                      new TNode<int>(7,
                                                     new TNode<int>(2),
                                                     new TNode<int>(6,
                                                                    new TNode<int>(5),
                                                                    new TNode<int>(11))),
                                      new TNode<int>(9,
                                                     nullptr,
                                                     new TNode<int>(9,
                                                                    new TNode<int>(5),
                                                                    nullptr)));

    root = removeBigLeaves(root);

    printTree(root);

    freeTree(root);

    return 0;
}