#include <iostream>
#include <list>
#include <queue>
#include <string>

bool isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

int getTopAndPop(std::stack<int> &s)
{
    int result = s.top();
    s.pop();

    return result;
}

int evaluateExpression(std::queue<char> expression)
{
    std::stack<int> numbers;

    while (!expression.empty())
    {
        char currentSymbol = expression.front();
        expression.pop();

        if (isNumber(currentSymbol))
        {
            numbers.push(currentSymbol - '0');
            continue;
        }

        bool enoughNumbersForExpression = (numbers.size() >= 2);

        if (!enoughNumbersForExpression)
        {
            throw std::logic_error("The expression is not valid - not enough numbers before operation");
        }

        int number1 = getTopAndPop(numbers);
        int number2 = getTopAndPop(numbers);

        int newNumber = 0;

        switch (currentSymbol)
        {
        case '+':
            newNumber = number2 + number1;
            break;

        case '-':
            newNumber = number2 - number1;
            break;

        case '*':
            newNumber = number2 * number1;
            break;

        case '/':
            newNumber = number2 / number1;
            break;

        default:
            throw std::logic_error("The expression is not valid - contains not a valid operation");
        }

        numbers.push(newNumber);
    }

    if (numbers.size() != 1)
    {
        throw std::logic_error("The expression is not valid - doesn't have enough operations");
    }

    return numbers.top();
}

bool isSymmetric(const std::list<std::queue<char>> &input)
{
    auto begin = input.begin();
    auto end = input.end();

    if (begin == end)
    {
        return true;
    }

    --end;

    while (begin != end)
    {
        int resultBegin = evaluateExpression(*begin);
        int resultEnd = evaluateExpression(*end);

        if (resultBegin != resultEnd)
        {
            return false;
        }

        ++begin;
        --end;
    }

    return true;
}

std::queue<char> makeTestQueue(const std::string &expression)
{
    std::queue<char> result;

    for (auto c : expression)
    {
        result.push(c);
    }

    return result;
}

int main()
{
    std::list<std::queue<char>> test = {
        makeTestQueue("45+"),
        makeTestQueue("16+7*"),
        makeTestQueue("84+"),
        makeTestQueue("177**"),
        makeTestQueue("23*3+")};

    if (isSymmetric(test))
    {
        std::cout << "The list is symmetric\n";
    }
    else
    {
        std::cout << "The list is not symmetric\n";
    }

    return 0;
}