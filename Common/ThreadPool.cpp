#include "stdafx.h"
#include "ThreadPool.h"
#include"Thread.h"

ThreadPool::ThreadPool(int32 poolSize):_threadNum(poolSize),
_mutex(),_condition(new ThreadCondition(_mutex)){

}

void ThreadPool::start(){
    
    for(int32 i = 0;i < _threadNum;++i){
        ThreadPtr thread = std::make_shared<Thread>(std::bind(&ThreadPool::thread_func,this));
        _threadPool.push_back(thread);
        thread->start();
    }
}

void ThreadPool::thread_func(){
    while(_running){
        AutoLock autoLock(&_mutex);
        _condition->wait();
        Task task(take());
        task();
    }
}

ThreadPool::Task ThreadPool::take(){
    AutoLock autoLock(&_mutex);

    Task task = _taskDeque.front();
    _taskDeque.pop_front();
    return task;
}

void ThreadPool::runInThread(Task task){
    AutoLock autoLock(&_mutex);

    _taskDeque.push_back(task);
    _condition->notify();
}