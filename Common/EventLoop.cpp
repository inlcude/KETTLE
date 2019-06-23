#include "stdafx.h"
#include "EventLoop.h"
#include "EpollPoller.h"

EventLoop::EventLoop():_running(false),
_poller(new EpollPoller()){

}

EventLoop::~EventLoop(){

}

void EventLoop::runInLoop(const Channel* channel){

}

void EventLoop::startLoop(){
    
    while(_running){

    }
}

void EventLoop::stopLoop(){

}