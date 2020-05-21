#include "stdafx.h"
#include "EventLoop.h"
#include "EpollPoller.h"

EventLoop::EventLoop():_running(true),
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

void EventLoop::updateChannel(Channel* channel)
{
    _poller->updateChannel(channel);
}

void EventLoop::stopLoop(){
    _running = false;
}

void EventLoop::startLoop(){

}
void EventLoop::loop(){
    while(_running){
        _poller->poller();
    }
}