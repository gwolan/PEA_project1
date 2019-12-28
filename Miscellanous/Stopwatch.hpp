#pragma once

#include <ctime>


class Stopwatch
{
    public:
        Stopwatch();
        void start();
        void stop();
        double read();
        double measurement;
    protected:
    private:
        clock_t tstart;
        clock_t tstop;
};
