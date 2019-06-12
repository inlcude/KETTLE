#include "stdafx.h"
#include "AsynLog.h"
#include "LoggerStream.h"
#include"ThreadCondition.h"

AsynLog::AsynLog():
_thread(std::bind(&AsynLog::thread_func,this)),
_running(false),
_latch(1),
_mutex(){
    _condition.reset(new ThreadCondition(_mutex));
}

AsynLog::~AsynLog(){

}

void AsynLog::thread_func(){
    _latch.countdown();
    while(_running){

    }

    _condition->notifyAll();
}

void AsynLog::start(){
    _running = true;
    _thread.start();
    _latch.wait();
}

void AsynLog::stop(){
    AutoLock autoLock(&_mutex);
    _running = false;
    _condition->wait();
}