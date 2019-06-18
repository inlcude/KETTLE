#ifndef __TIMER_QUENE_H
#define __TIMER_QUENE_H
#include"KETTLEPlatform.h"
#include"Log.h"

using namespace KETTLE;
namespace KETTLE{
    class TimerQuene;
    
class Timer{
    friend class TimerQuene;
    typedef std::function<void()> CallBack;
public:
    Timer(int _interval,int _repeat,CallBack _cb) : 
    interval_(_interval)
    ,sequnece_(sequence++)
    ,repeat_(_repeat)
    ,cb(_cb){
    }

    void Trigger(){
        cb();
    }
private:
    int         interval_;
    int         num_;
    int         slot_;
    int         sequnece_;
    int         repeat_;
    CallBack    cb;

    static std::atomic_ullong sequence;
};

std::atomic_ullong Timer::sequence(0);

// don't use epoll ET model,please use epoll LT model;
class TimerQuene{
    typedef std::list<Timer*> TimerList;
    typedef TimerList::iterator ListIter;
    typedef std::vector<TimerList> TimerContainer;
    typedef std::function<void()> CallBack;
public:
    TimerQuene();
    ~TimerQuene();

    void register_timer(Timer* timer);
    void unregister_timer(int sequence);

    void tick();

    int32         getTimerfd(){return timer_fd;}
private:
    int32                 timer_fd;
    TimerContainer      container_;
    int curslot;
    static const int Time_Inerval = 100;
    static const int Time_Wheel = 10;       
};

const int TimerQuene::Time_Inerval;
const int TimerQuene::Time_Wheel;
}
#endif