#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 30;
const int MAX_STATEMENT_LENGTH = 150;
const int MAX_PROBLEMS_COUNT = 8;

class Problem
{
    char name[MAX_NAME_LENGTH];
    char statement[MAX_STATEMENT_LENGTH];
    int points;

    bool isValidName(const char *name) const
    {
        return strlen(name) > MAX_NAME_LENGTH;
    }

    bool isValidStatement(const char *statement) const
    {
        return strlen(statement) > MAX_STATEMENT_LENGTH;
    }

public:
    Problem()
    {
        this->points = 0;
    }

    Problem(const char *name, const char *statement, int points)
    {
        setName(name);
        setStatement(statement);
        setPoints(points);
    }

    void setName(const char *newName)
    {
        if (!isValidName(newName))
        {
            cout << "Name should be max " << MAX_NAME_LENGTH << " characters\n";
            return;
        }

        strcpy(this->name, newName);
    }

    void setStatement(const char *newStatement)
    {
        if (!isValidStatement(newStatement))
        {
            cout << "Statement should be max " << MAX_STATEMENT_LENGTH << " characters\n";
            return;
        }

        strcpy(this->statement, newStatement);
    }

    void setPoints(int newPoints)
    {
        this->points = newPoints;
    }

    int getPoints() const
    {
        return points;
    }
};

class Exam
{
    int problemsCount;
    Problem problems[MAX_PROBLEMS_COUNT];
    int minimumRequiredPoints;

public:
    Exam(int problemsCount, const Problem *problems, int minimumRequiredPoints)
    {
        if (problemsCount > MAX_PROBLEMS_COUNT)
        {
            cout << "Maximum problems count is " << problemsCount << endl;

            return;
        }

        this->problemsCount = problemsCount;

        for (int i = 0; i < problemsCount; ++i)
        {
            this->problems[i] = problems[i];
        }

        this->minimumRequiredPoints = minimumRequiredPoints;
    }

    void changMin(int newMinimumRequiredPoints)
    {
        this->minimumRequiredPoints = newMinimumRequiredPoints;
    }

    int getMax() const
    {
        int currentPoints = 0;

        for (int i = 0; i < problemsCount; ++i)
        {
            currentPoints += problems[i].getPoints();
        }

        return currentPoints;
    }
};