#include <iostream>

using namespace std;

void printSymbol(char symbol, int counter)
{
    for (int i = 0; i < counter; ++i)
    {
        cout << symbol;
    }
}

int main()
{
    int n;
    cin >> n;

    char whitespace = ' ';

    char underscore = '_';

    char pipe = '|';

    for (int i = 0; i < 2 * n; ++i)
    {
        printSymbol(whitespace, 3 * n + 2);

        cout << pipe;

        if (i == 0)
        {
            cout << ">";
        }

        cout << endl;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        printSymbol(whitespace, 3 * n + 2 - i - 1);

        cout << "/";

        printSymbol(whitespace, 2 * i + 1);

        cout << "\\" << endl;
    }

    for (int i = 0; i <= n; ++i)
    {
        cout << (i > 0 ? pipe : whitespace);

        printSymbol(underscore, n);

        cout << (i > 0 ? pipe : whitespace);

        printSymbol(whitespace, n - i);

        cout << "/";

        char middleCharacter = (i == n ? underscore : whitespace);
        printSymbol(middleCharacter, 2 * (n - 1 + i) + 1);

        cout << "\\";

        printSymbol(whitespace, n - i);

        cout << (i > 0 ? pipe : whitespace);

        printSymbol(underscore, n);

        cout << (i > 0 ? pipe : whitespace) << endl;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        cout << pipe;

        printSymbol(underscore, n);

        cout << pipe;

        printSymbol(whitespace, 4 * n + 1);

        cout << pipe;

        printSymbol(underscore, n);

        cout << pipe << endl;
    }

    for (int i = 0; i <= n; ++i)
    {
        cout << pipe;

        printSymbol(underscore, n);

        cout << pipe;

        int middleCharacterCounter = n + ((n - 1) % 2);
        int whitespaceCounter = (4 * n - 1 - middleCharacterCounter) / 2;

        printSymbol(whitespace, whitespaceCounter);

        cout << (i == 0 ? whitespace : pipe);

        char middleCharacter = (i == 0 ? underscore : whitespace);
        printSymbol(middleCharacter, middleCharacterCounter);

        cout << (i == 0 ? whitespace : pipe);

        printSymbol(whitespace, whitespaceCounter);

        cout << pipe;

        printSymbol(underscore, n);

        cout << pipe << endl;
    }

    return 0;
}