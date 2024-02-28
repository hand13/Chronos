#include <chrono>
using namespace std::chrono;
#include "Timer.h"
static long long epoch_time(){
    time_point<system_clock> now = system_clock::now();
    time_point<system_clock,milliseconds> ms = time_point_cast<milliseconds>(now);
    return ms.time_since_epoch().count();
}
namespace Chronos{
    void Timer::start(){
        lastEpochTime = epoch_time();
        startEpochTime = lastEpochTime;
    }

    long long Timer::elpasedTimeFromStart()const{
        return epochTime() - startEpochTime;
    }

    long long Timer::epochTime()const {
        return epoch_time();
    }

    unsigned int Timer::delta(){
        long long tmp = epoch_time();
        unsigned int delta = tmp - lastEpochTime;
        lastEpochTime = tmp;
        return delta;
    }
}
