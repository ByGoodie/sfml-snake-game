#include "timer.h"

timer::timer(double endp) {
    start = clock();
    cur = 0.0;
    end = endp;
    stopped = false;
}

void timer::calcTime() {
    if (!stopped) {
        clock_t tRange;
        if ((tRange = clock() - start) > 0) {
            cur += (double)((double)tRange / (double)CLOCKS_PER_SEC);
            start = clock();
        }
    }
}

void timer::tContinue() {
    start = clock();
    stopped = false;
}

void timer::tStop() {
    stopped = true;
}

void timer::reset() {
    start = clock();
    cur = 0;
    stopped = false;
}

bool timer::isFinish() {
    if (cur >= end) {
        return true;
    }

    return false;
}