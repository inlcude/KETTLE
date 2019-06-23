#include"Thread.h"
#include"ThreadTask.h"
#include"Thread.h"
#include"Log.h"

static void* ThreadFunction(void* param){
    Thread* pThread = (Thread*)param;
    pThread->loop();

    return (void*)0;
}

Thread::Thread(ThreadFunc func)
: _func(func),_tid(0),_countDown(1){

}

Thread::~Thread(){
    pthread_detach(_tid);
}

void KETTLE::Thread::start(){
    if(pthread_create(&_tid,NULL,&ThreadFunction,this) != 0)
        LOG_FATA << "create thread error" << " reson:" << strerror(errno); 
    
    _countDown.wait();
    _running = true;
}

void KETTLE::Thread::stop(){
    _running = false;
    join();
}

void KETTLE::Thread::loop(){
    _countDown.countdown();
    _func();
}

void Thread::join(){
    if(pthread_join(_tid,NULL) != 0)
        LOG_FATA << "thread join failed,thread id:" << _tid << " reson:" << strerror(errno);

}