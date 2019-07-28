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
void EventLoop::stopLoop(){

}

void EventLoop::loop(){
    while(_running){
        _poller->poller();
    }
}