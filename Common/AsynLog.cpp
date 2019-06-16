#include "stdafx.h"
#include "AsynLog.h"
#include "LoggerStream.h"
#include"ThreadCondition.h"
#include "LoggerFile.h"

AsynLog::AsynLog():
_thread(std::bind(&AsynLog::thread_func,this)),
_running(false),
_latch(1),
_mutex(),
_condition(new ThreadCondition(_mutex)),
_file(new LoggerFile()){
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

void AsynLog::append(const char* log,int32 len){
    if(!_running)
        return;
    
    AutoLock lock(&_mutex);
    if(_currentbuffer->availd() > len)
        *_currentbuffer << log;
    else{
        _buffers.push_back(std::move(_currentbuffer));

        if(_nextbuffer)
            _currentbuffer = std::move(_nextbuffer);
        else
            _currentbuffer.reset(new LargeLoggerStream());

        *_currentbuffer << log;
        _condition->notify();
    }

}