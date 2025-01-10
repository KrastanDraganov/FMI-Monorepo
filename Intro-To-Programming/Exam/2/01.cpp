#include <iostream>

using namespace std;

void mySwap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

int myStrlen(const char *s)
{
    if (!s)
    {
        return 0;
    }

    int counter = 0;

    while (*s)
    {
        ++counter;
        ++s;
    }

    return counter;
}

bool isInterval(char character)
{
    return character == ' ';
}

bool isLowerCaseLetter(char character)
{
    return character >= 'a' && character <= 'z';
}

bool isValidInput(const char *text)
{
    if (!text)
    {
        cout << "Text is empty!\n";
        return false;
    }

    while (*text)
    {
        if (!isInterval(*text) && !isLowerCaseLetter(*text))
        {
            cout << "Text should contain only lowercase letters and intervals!\n";

            return false;
        }

        ++text;
    }

    return true;
}

void reverseWord(char *text, int wordStartIndex, int wordEndIndex)
{
    if (!text)
    {
        return;
    }

    int leftIndex = wordStartIndex;
    int rightIndex = wordEndIndex;

    while (leftIndex < rightIndex)
    {
        swap(text[leftIndex], text[rightIndex]);

        ++leftIndex;
        --rightIndex;
    }
}

void reverseWordsIn(char *text)
{
    if (!text)
    {
        return;
    }

    int textSize = myStrlen(text);

    int wordStartIndex = -1;

    for (int i = 0; i <= textSize; ++i)
    {
        if (i == textSize || isInterval(text[i]))
        {
            if (wordStartIndex != -1)
            {
                reverseWord(text, wordStartIndex, i - 1);
                wordStartIndex = -1;
            }
        }
        else if (wordStartIndex == -1)
        {
            wordStartIndex = i;
        }
    }
}

int main()
{
    char text[] = "I like to code";

    if (!isValidInput(text))
    {
        return 1;
    }

    reverseWordsIn(text);

    cout << text << endl;

    return 0;
}
