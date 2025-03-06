#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 16;

enum class Specialty
{
    Informatics,
    Mathematics,
    ComputerScience,
    SoftwareEngineering
};

class Student
{
private:
    char firstName[MAX_NAME_LENGTH + 1];
    char lastName[MAX_NAME_LENGTH + 1];

    int facultyNumber;

    Specialty specialty;

    double averageGrade;

    char *getSpecialtyName() const
    {
        switch (specialty)
        {
        case Specialty::Informatics:
            return "Informatics";

        case Specialty::Mathematics:
            return "Mathematics";

        case Specialty::ComputerScience:
            return "Computer Science";

        case Specialty::SoftwareEngineering:
            return "Software Engineering";

        default:
            return "";
        }
    }

public:
    void print() const
    {
        cout << firstName << " " << lastName << ", " << facultyNumber << ", " << averageGrade << " in " << getSpecialtyName() << endl;
    }
};