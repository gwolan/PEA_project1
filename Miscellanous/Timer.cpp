#include <Miscellanous/Timer.hpp>


Timer::Timer()
    : begin()
    , end()
{ }

void Timer::start()
{
    begin = std::chrono::system_clock::now();
}

void Timer::stop()
{
    end = std::chrono::system_clock::now();
}

double Timer::getTime()
{
    std::chrono::duration<double> result = end - begin;
    return result.count();
}
