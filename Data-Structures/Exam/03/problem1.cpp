#include <iostream>
#include <string>
#include <set>

struct Node
{
    char symbol;

    Node *left;
    Node *middle;
    Node *right;

    Node(char symbol, Node *left, Node *middle, Node *right) : symbol(symbol), left(left), middle(middle), right(right) {}
};

void traverseTree(Node *node, std::string &currentWord, std::set<std::string> &allWords)
{
    if (!node)
    {
        return;
    }

    bool isLeaf = true;

    currentWord += node->symbol;

    if (node->left)
    {
        traverseTree(node->left, currentWord, allWords);
        isLeaf = false;
    }

    if (node->middle)
    {
        traverseTree(node->middle, currentWord, allWords);
        isLeaf = false;
    }

    if (node->right)
    {
        traverseTree(node->right, currentWord, allWords);
        isLeaf = false;
    }

    if (isLeaf)
    {
        allWords.insert(currentWord);
    }

    currentWord.pop_back();
}

std::set<std::string> findAllUniqueWords(Node *root)
{
    if (!root)
    {
        return {};
    }

    std::set<std::string> result;

    std::string currentWord = "";

    traverseTree(root, currentWord, result);

    return result;
}

void freeTree(Node *node)
{
    if (!node)
    {
        return;
    }

    if (node->left)
    {
        freeTree(node->left);
    }

    if (node->middle)
    {
        freeTree(node->middle);
    }

    if (node->right)
    {
        freeTree(node->right);
    }

    delete node;
}

int main()
{
    Node *root = new Node('a',
                          new Node('b',
                                   new Node('d', nullptr, nullptr, nullptr),
                                   nullptr,
                                   new Node('e', nullptr, nullptr, nullptr)),
                          new Node('c', nullptr, nullptr, nullptr),
                          new Node('b',
                                   nullptr,
                                   new Node('d', nullptr, nullptr, nullptr),
                                   nullptr));

    std::set<std::string> result = findAllUniqueWords(root);

    std::cout << "All unique sorted words are:\n";
    for (std::string word : result)
    {
        std::cout << word << "\n";
    }

    freeTree(root);

    return 0;
}