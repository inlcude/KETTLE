#include "stdafx.h"
#include "EventLoop.h"
#include "EpollPoller.h"

EventLoop::EventLoop():_running(false),
_poller(new EpollPoller()){

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
    AutoLock autoLock(&_mutex);
    _functors.push_back(functor);
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