#include <iostream>

using namespace std;

const int MONTHS_LIMIT = 12;

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year)
{
    switch (month)
    {
    case 2:
        return isLeapYear(year) ? 29 : 28;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    default:
        return 31;
    }
}

void printLeadingZero(int number)
{
    bool isSingleNumber = (number < 10);

    if (isSingleNumber)
    {
        cout << "0";
    }

    cout << number << ".";
}

void printFormattedDate(int day, int month, int year)
{
    printLeadingZero(day);
    printLeadingZero(month);
    cout << year << endl;
}

int getCountOfDaysBetweenDates(int startDay, int startMonth, int startYear,
                               int endDay, int endMonth, int endYear)
{
    bool isEndDayBeforeStartDay =
        (startYear > endYear ||
         (startYear == endYear && (startMonth > endMonth ||
                                   (startMonth == endMonth && startDay > endDay))));

    if (isEndDayBeforeStartDay)
    {
        return -1;
    }

    int daysCount = 0;

    while (startYear < endYear || startMonth < endMonth || startDay < endDay)
    {
        ++startDay;
        ++daysCount;

        int daysLimit = getDaysInMonth(startMonth, startYear);

        if (startDay > daysLimit)
        {
            startDay = 1;
            ++startMonth;
        }

        if (startMonth > MONTHS_LIMIT)
        {
            startMonth = 1;
            ++startYear;
        }
    }

    return daysCount;
}

void printDateAfter(int day, int month, int year, int countOfDays)
{
    for (int i = 0; i < countOfDays; ++i)
    {
        ++day;

        int daysLimit = getDaysInMonth(month, year);

        if (day > daysLimit)
        {
            day = 1;
            ++month;
        }

        if (month > MONTHS_LIMIT)
        {
            month = 1;
            ++year;
        }
    }

    printFormattedDate(day, month, year);
}

void printDateBefore(int day, int month, int year, int countOfDays)
{
    for (int i = 0; i < countOfDays; ++i)
    {
        --day;

        if (day < 1)
        {
            --month;

            if (month < 1)
            {
                month = MONTHS_LIMIT;
                --year;
            }

            day = getDaysInMonth(month, year);
        }
    }

    printFormattedDate(day, month, year);
}
