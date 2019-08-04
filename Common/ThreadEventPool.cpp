#include "ThreadEventPool.h"
#include "EventLoop.h"
#include "Thread.h"
#include "Log.h"


ThreadEventPool::ThreadEventPool(int32 threadNum):_threadNum(threadNum){
    if(_threadNum <= 0)
        LOG_FATA << "thread event pool num less then 0";
    _nCount = 0;
    _eventPool.resize(threadNum);
    _threadPool.resize(threadNum);
    for(int32 i = 0; i < threadNum;++i)
        _eventPool[i] = new EventLoop();

    for (int32 i = 0; i < threadNum; i++)
        _threadPool[i] = new Thread(std::bind(&EventLoop::loop,_eventPool[i]));
}

EventLoop* ThreadEventPool::getNextLoop(){
    int32 count = _nCount.load();
    _nCount++;

    return _eventPool[_nCount%_threadNum];
}

void ThreadEventPool::start(){
    for (int32 i = 0; i < _threadNum; i++)
        _threadPool[i]->start();
}