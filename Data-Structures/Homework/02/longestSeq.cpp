#include <iostream>
#include <vector>
#include <list>

template <class Iterator, class Predicate>
Iterator longestSeq(Iterator first, Iterator last, Predicate p)
{
    Iterator longestSeqStart = last;
    int longestSeqLength = 0;

    Iterator currentSeqStart = last;
    int currentSeqLength = 0;

    for (Iterator it = first; it != last; ++it)
    {
        if (!p(*it))
        {
            if (currentSeqLength > longestSeqLength)
            {
                longestSeqLength = currentSeqLength;
                longestSeqStart = currentSeqStart;
            }

            currentSeqLength = 0;

            continue;
        }

        if (currentSeqLength == 0)
        {
            currentSeqStart = it;
        }

        ++currentSeqLength;
    }

    if (currentSeqLength > longestSeqLength)
    {
        longestSeqLength = currentSeqLength;
        longestSeqStart = currentSeqStart;
    }

    return longestSeqStart;
}

bool testPredicate(int number)
{
    return number % 2 == 0;
}

void demoLongestSeqVector()
{
    std::cout << "Demo longestSeq with vector<int>:\n";

    std::vector<int> numbers{1, 2, 4, 6, 7, 8, 10, 12, 14, 1, 3, 5};

    auto result = longestSeq(numbers.begin(), numbers.end(), testPredicate);

    if (result != numbers.end())
    {
        std::cout << "vector: Found longest subsequence: ";

        for (auto it = result; it != numbers.end() && testPredicate(*it); ++it)
        {
            std::cout << *it << " ";
        }

        std::cout << "\n";
    }
    else
    {
        std::cout << "vector: No matching subsequence found\n";
    }
}

void demoLongestSeqList()
{
    std::cout << "Demo longestSeq with list<int>:\n";

    std::list<int> numbers{5, 6, 8, 10, 11, 13, 2, 4, 6, 8, 9};

    auto result = longestSeq(numbers.begin(), numbers.end(), testPredicate);

    if (result != numbers.end())
    {
        std::cout << "list: Found longest subsequence: ";

        for (auto it = result; it != numbers.end() && testPredicate(*it); ++it)
        {
            std::cout << *it << " ";
        }

        std::cout << "\n";
    }
    else
    {
        std::cout << "list: No matching subsequence found\n";
    }
}

int main()
{
    demoLongestSeqVector();
    demoLongestSeqList();

    return 0;
}