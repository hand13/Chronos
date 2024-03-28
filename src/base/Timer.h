#pragma once
namespace Chronos {
class Timer {
   private:
    long long startEpochTime;
    long long lastEpochTime;  // microsecond
   public:
    void start();
    long long epochTime() const;
    long long elpasedTimeFromStart() const;
    unsigned int delta();
};
}  // namespace Chronos