#include <Poco/Mutex.h>
#include <Poco/Task.h>
#include <Poco/TaskManager.h>
// #include <Poco/Runnable.h>
// #include <Poco/Thread.h>
// #include <Poco/ThreadPool.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>
class Tmp : public Poco::Task{
    virtual void runTask()override {
        mt.lock();
        std::cout<<m<<std::endl;
        m++;
        mt.unlock();
    }
    public:
    Tmp(volatile int& target,Poco::Mutex& mt,const std::string& name):Poco::Task(name),m(target),mt(mt){}
    volatile int& m;
    Poco::Mutex& mt;
};
int main() {
    // Poco::ThreadPool& tp = Poco::ThreadPool::defaultPool();
    // tp.available();
    Poco::TaskManager tm;
    Poco::Mutex m;
    volatile int s = 0;
    for(int i = 0;i<100;i++) {
        tm.start(new Tmp(s,m,"task" + std::to_string(i)));
    }
    tm.joinAll();
    return 0;
};