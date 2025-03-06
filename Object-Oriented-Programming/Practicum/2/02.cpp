#include <iostream>

using namespace std;

bool isInInterval(int target, int left, int right)
{
    return left <= target && target <= right;
}

class Point
{
private:
    int x;
    int y;

public:
    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    bool isBetweenTwoPoints(const Point &p1, const Point &p2) const
    {
        return isInInterval(x, p1.x, p2.x) && isInInterval(y, p1.y, p2.y);
    }

    bool isLowerThan(const Point &other) const
    {
        return x <= other.x && y <= other.y;
    }
};

class Rectangle
{
private:
    Point leftPoint;
    Point rightPoint;

    int getHeight()
    {
        return abs(rightPoint.getX() - leftPoint.getX());
    }

    int getWidth()
    {
        return abs(rightPoint.getY() - leftPoint.getY());
    }

public:
    Rectangle() {}

    Rectangle(const Point &leftPoint, const Point &rightPoint)
    {
        if (leftPoint.isLowerThan(rightPoint))
        {
            cout << "Left corner point should be lower than right corner point!\n";

            return;
        }

        this->leftPoint = leftPoint;
        this->rightPoint = rightPoint;
    }

    int calculatePerimeter()
    {
        int height = getHeight();
        int width = getWidth();

        return 2 * (height + width);
    }

    int calculateSquare()
    {
        int height = getHeight();
        int width = getWidth();

        return height * width;
    }

    bool overlap(const Rectangle &other)
    {
        return leftPoint.isBetweenTwoPoints(other.leftPoint, other.rightPoint) || rightPoint.isBetweenTwoPoints(other.leftPoint, other.rightPoint);
    }
};
