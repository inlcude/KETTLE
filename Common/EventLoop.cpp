#include "stdafx.h"
#include "EventLoop.h"
#include "EpollPoller.h"

EventLoop::EventLoop():_running(false),
_poller(new EpollPoller())
,_eventfd(::eventfd(0,EFD_CLOEXEC|EFD_NONBLOCK))
,_eventChannel(new Channel(_eventfd
,std::bind(&EventLoop::handRead,this)
,std::bind(&EventLoop::handWrite,this)
.std::bind(&EventLoop::handError,this)))
{
    _poller->runInLoop(_eventChannel.get());
}

EventLoop::~EventLoop(){

}

void EventLoop::runInLoop(Channel* channel){
    _poller->registerInPoller(channel);
}

void EventLoop::removeChannel(Channel* channel){
    _poller->removeChannel(channel);
}

void EventLoop::startLoop(){

}

void EventLoop::stopLoop(){

}

void EventLoop::runInLoop(std::function<void()> functor){
    {
     AutoLock autoLock(&_mutex);
    _functors.push_back(std::move(functor)); 
    }
    wakeUp();
}

void EventLoop::wakeUp(){
    uint64_t one = 1;
    size_t nsize = ::write(_eventfd,&one,sizeof(one));
    if (nsize != sizeof(uint64_t))
        LOG_FATA << "EventLoop::wakeUp error,reason" << ::strerror(errno);
}

void EventLoop::loop(){
    while(_running){
        _poller->poller();

        std::vector<std::function<void()>> temp;

        {
            AutoLock autoLock(&_mutex);
            temp.swap(_functors);
        }

        for(auto& it : temp)
            it();
    }
}