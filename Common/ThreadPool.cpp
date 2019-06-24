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

}