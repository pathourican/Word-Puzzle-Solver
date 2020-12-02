// This timer typically has 1/1000000 second (1 micro-second) accuracy
// under most Linux distributions

// Patrick Hourican
// pjh4as
// 10/14/2020
// timer.h

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class timer {
public:
    timer();
    timer(timer& myTimer);
    void start();
    void stop();

    // Returns the time elapsed, in seconds
    double getTime();
private:
    steady_clock::time_point start_time, stop_time;
    bool running;

  friend class wordPuzzle;

};

ostream& operator<<(ostream& theStream, timer& theTimer);

#endif
