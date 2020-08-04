#include "stdafx.h"
#include "Timer.h"
#include "EventLoop.h"

TimerQuene::TimerQuene() : curslot(0){
    container_.resize(Time_Wheel);
    timer_fd = timerfd_create(CLOCK_MONOTONIC,TFD_CLOEXEC | TFD_NONBLOCK);
    if(timer_fd < 0)
        err_exit(errno,"creat timer fd error");

    struct itimerspec new_timer;
    struct timespec cur;
    clock_gettime(CLOCK_REALTIME,&cur);
    memset(&new_timer,0,sizeof(new_timer));

    new_timer.it_interval.tv_nsec = Time_Inerval * 1000 * 1000;
    new_timer.it_interval.tv_sec = Time_Inerval / 1000;
    new_timer.it_value.tv_nsec = Time_Inerval * 1000 * 1000;
    new_timer.it_value.tv_sec = Time_Inerval / 1000;
    if(timerfd_settime(timer_fd,0,&new_timer,nullptr) != 0)
        err_exit(errno,"set time error");
}

TimerQuene::~TimerQuene(){
    close(timer_fd);
}

void TimerQuene::register_timer(Timer* timer){
    int interval = 0;
    if(timer->interval_ < Time_Inerval)
        interval = Time_Inerval;
    else
        interval = timer->interval_;

    timer->num_ = interval / (Time_Inerval * Time_Wheel);
    int a =timer->num_ * Time_Inerval;
    int b = interval - a;
    int c = b / Time_Inerval;
    timer->slot_ = (curslot + c) % Time_Wheel;

    container_[timer->slot_].push_back(timer);
}

void TimerQuene::unregister_timer(int sequence){

}

void TimerQuene::tick(){
    TimerList& list = container_[curslot];
    ListIter iter = list.begin();
    while(iter != list.end()){
        printf("current slot: %d\n",curslot);
        if((*iter)->num_ > 0){
            (*iter)->num_--;
            ++iter;
        }
        else{
            (*iter)->cb();

            int interval = 0;
            if((*iter)->interval_ < Time_Inerval)
                interval = Time_Inerval;
            else
                interval = (*iter)->interval_;
            (*iter)->num_ = interval / (Time_Inerval * Time_Wheel);
            int a = (*iter)->num_ * Time_Inerval;
            int b = interval - a;
            int c = b / Time_Inerval;
            (*iter)->slot_ = (curslot + c) % Time_Wheel;

            container_[(*iter)->slot_].push_back(*iter);
            iter = list.erase(iter);
        }
    }
    curslot = (++curslot) % Time_Wheel;
}