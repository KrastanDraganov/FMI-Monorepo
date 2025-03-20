#pragma once

#include <iostream>

const int MAX_NAME_LEN = 32;
const int MAX_STOPS_COUNT = 16;

class Metro
{
private:
    bool isDrivingForward = true;

    int stopsCount = 0;
    char *stops[MAX_STOPS_COUNT];

    char manufacture[MAX_NAME_LEN + 1] = "";
    char model[MAX_NAME_LEN + 1] = "";

    char idNumber[MAX_NAME_LEN + 1] = "";

    char currentStop[MAX_NAME_LEN + 1] = "";

public:
    Metro() = default;

    Metro(bool isDrivingForward, int stopsCount, char **stops, char *manufacture, char *model, char *idNumber, char *currentStop);

    void changeRoute(int position, char *newStop, bool isAdded);
};