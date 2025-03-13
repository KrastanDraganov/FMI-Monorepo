#include <iostream>

#include "Time.h"

using namespace std;

bool Time::isValidHour(int hour) const
{
    return (hour >= 0 && hour < MAX_HOUR);
}

bool Time::isValidMinute(int minutes) const
{
    return (minutes >= 0 && minutes < MAX_MINUTES);
}

bool Time::isValidSecond(int seconds) const
{
    return (seconds >= 0 && seconds < MAX_SECONDS);
}

void Time::addMinutes(int count)
{
    this->minutes = (count % MAX_MINUTES);
    addHours(count / MAX_MINUTES);
}

void Time::addHours(int count)
{
    this->hour = (count % MAX_HOUR);
}

Time::Time(int hour, int minutes, int seconds)
{
    if (!isValidHour(hour) || !isValidMinute(minutes) || !isValidSecond(seconds))
    {
        setHour(0);
        setMinutes(0);
        setSeconds(0);
    }
    else
    {
        setHour(hour);
        setMinutes(minutes);
        setSeconds(seconds);
    }
}

void Time::setHour(int newHour)
{
    if (isValidHour(newHour))
    {
        this->hour = newHour;
    }
}

void Time::setMinutes(int newMinutes)
{
    if (isValidMinute(newMinutes))
    {
        this->minutes = newMinutes;
    }
}

void Time::setSeconds(int newSeconds)
{
    if (isValidSecond(newSeconds))
    {
        this->seconds = newSeconds;
    }
}

void Time::addSeconds(int count)
{
    this->seconds = (count % MAX_SECONDS);
    addMinutes(count / MAX_SECONDS);
}

void Time::removeSeconds(int count)
{
    addSeconds(-count);
}

const char *Time::getPartOfTheDay() const
{
    return (this->hour >= AFTERNOON_THRESHOLD_HOUR ? "PM" : "AM");
}

void Time::printAmericanFormat() const
{
    cout << getHour() % AFTERNOON_THRESHOLD_HOUR << ":" << getMinutes() << ":" << getSeconds() << " " << getPartOfTheDay() << endl;
}

bool Time::isLaterThan(const Time &comp) const
{
    if (getHour() == comp.hour)
    {
        if (getMinutes() == comp.minutes)
        {
            return getSeconds() > comp.seconds;
        }

        return getMinutes() > comp.minutes;
    }

    return getHour() > comp.hour;
}

int Time::remainingSecondsToNextHour() const
{
    return (MAX_SECONDS - getSeconds()) + (MAX_MINUTES - getMinutes()) * MAX_SECONDS;
}

void Time::printRemainingTimeToNoon() const
{
    cout << "Left time " << MAX_HOUR - getHour() << ":" << MAX_MINUTES - getMinutes() << ":" << MAX_SECONDS - getSeconds() << endl;
}