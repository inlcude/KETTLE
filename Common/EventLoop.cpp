#include "stdafx.h"
#include "KETTLEPlatform.h"
#include "EventLoop.h"
#include "EpollPoller.h"
#include "Log.h"
#include "Channel.h"
#include "TemplateFunctions.h"

EventLoop::EventLoop():_running(false),
_poller(new EpollPoller())
,_eventfd(::eventfd(0,EFD_CLOEXEC|EFD_NONBLOCK))
,_eventChannel(new Channel( this
                            ,_eventfd
                            ,std::bind(&EventLoop::handRead,this)
                            ,std::bind(&EventLoop::handWrite,this)
                            ,std::bind(&EventLoop::handError,this)))

{
    _poller->registerInPoller(_eventChannel.get());
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
    _running = true;
    this->loop();
}


void EventLoop::updateChannel(Channel* channel)
{
    _poller->updateChannel(channel);
}

void EventLoop::stopLoop(){
    _running = false;
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
    LOG_INFO << "thread: " << CommonFunction::GetSelfThreadId() << " started...";
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
    LOG_INFO << "thread: " << CommonFunction::GetSelfThreadId() << " exit...";
}

void EventLoop::handRead(){

}

void EventLoop::handWrite(){

}

void EventLoop::handError(){

}