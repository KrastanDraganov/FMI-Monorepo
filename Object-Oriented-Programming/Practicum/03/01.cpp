#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 30;

struct Name
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
};

class Teacher
{
    char name[MAX_NAME_LENGTH];
    int age;
    int yearsOfExperience;

public:
    Teacher(const char *name, int age, int yearsOfExperience)
    {
        if (strlen(name) > MAX_NAME_LENGTH)
        {
            cout << "Name should be max " << MAX_NAME_LENGTH << " characters!\n";

            return;
        }

        if (yearsOfExperience > age)
        {
            cout << "Age should be bigger than years of experience\n";

            return;
        }

        strcpy(this->name, name);

        this->age = age;
        this->yearsOfExperience = yearsOfExperience;
    }

    char *getName()
    {
        return name;
    }

    int getAge()
    {
        return age;
    }

    int getYearsOfExperience()
    {
        return yearsOfExperience;
    }

    void setName(const char *newName)
    {
        strcpy(this->name, newName);
    }

    void setAge(int newAge)
    {
        age = newAge;
    }

    void setYearsOfExperience(int newYearsOfExperience)
    {
        yearsOfExperience = newYearsOfExperience;
    }
};
