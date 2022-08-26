#pragma once
#include <ctime>

extern "C";

class timer {
private:
    clock_t start;
    double end, cur;
    bool stopped;

public:
    timer(double endp);

    void calcTime();

    void tContinue();

    void tStop();

    void reset();

    bool isFinish();
};