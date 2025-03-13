#include <iostream>

const int MAX_HOUR = 24;
const int MAX_MINUTES = 60;
const int MAX_SECONDS = 60;

const int AFTERNOON_THRESHOLD_HOUR = 12;

class Time
{
private:
    int hour = 0;
    int minutes = 0;
    int seconds = 0;

    bool isValidHour(int hour) const;

    bool isValidMinute(int minutes) const;

    bool isValidSecond(int seconds) const;

    void addMinutes(int count);

    void addHours(int count);

public:
    Time() = default;

    Time(int hour, int minutes, int seconds);

    void setHour(int newHour);

    void setMinutes(int newMinutes);

    void setSeconds(int newSeconds);

    int getHour() const;

    int getMinutes() const;

    int getSeconds() const;

    void addSeconds(int count);

    void removeSeconds(int count);

    const char *getPartOfTheDay() const;

    void printAmericanFormat() const;

    bool isLaterThan(const Time &comp) const;

    int remainingSecondsToNextHour() const;

    void printRemainingTimeToNoon() const;
};