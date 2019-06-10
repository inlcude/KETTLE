#include"Thread.h"
#include"ThreadTask.h"
#include"Thread.h"
#include"Log.h"

using namespace KETTLE;
static void* ThreadFunction(void* param){
    Thread* pThread = (Thread*)param;
    pThread->loop();

    return (void*)0;
}

KETTLE::Thread::Thread(ThreadFunc func)
: _func(func),_tid(0){

}

void KETTLE::Thread::start(){
    if(pthread_create(NULL,NULL,&ThreadFunction,this) != 0)
        err_sys("create thread error",strerror(errno)); 
    
    _running = true;
}

void KETTLE::Thread::stop(){
    _running = false;
}

void KETTLE::Thread::loop(){
    while(_running){
        _func();
    }
}