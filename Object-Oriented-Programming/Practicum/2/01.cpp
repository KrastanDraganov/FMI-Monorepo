#include <iostream>

using namespace std;

struct Complex
{
    int a;
    int b;
};

void print(const Complex &number)
{
    cout << number.a << "+" << number.b << "i\n";
}

Complex sum(const Complex &number1, const Complex &number2)
{
    Complex result;

    result.a = number1.a + number2.a;
    result.b = number1.b + number2.b;

    return result;
}

Complex sub(const Complex &number1, const Complex &number2)
{
    Complex result;

    result.a = number1.a - number2.a;
    result.b = number1.b - number2.b;

    return result;
}

Complex mult(const Complex &number1, const Complex &number2)
{
    Complex result;

    result.a = number1.a * number2.a - number1.b * number2.b;
    result.b = number1.a * number2.b + number1.b * number2.a;

    return result;
}

int main()
{
    Complex a{1, 2};
    Complex b{2, 3};

    Complex result = mult(a, b);

    print(result);

    return 0;
}