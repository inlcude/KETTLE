#include "stdafx.h"
#include "AsynLog.h"
#include "LoggerStream.h"
#include"ThreadCondition.h"
#include "LoggerFile.h"
#include "CountDownLatch.h"

AsynLog::AsynLog():
_thread(std::bind(&AsynLog::thread_func,this)),
_running(false),
_latch(1),
_mutex(),
_condition(new ThreadCondition(_mutex)),
_file(new LoggerFile()),
_currentbuffer(new LargeLoggerStream),
_nextbuffer(new LargeLoggerStream){
}

AsynLog::~AsynLog(){

}

void AsynLog::thread_func(){
    _latch.countdown();
    LogBuffers buffers;
    LogBuffer buffer1(new LargeLoggerStream());
    LogBuffer buffer2(new LargeLoggerStream());
    while(_running){

        {
            AutoLock lock(&_mutex);
            // 等待日志发送信号解除
            if(buffers.empty())
                _condition->wait();
            _buffers.push_back(std::move(_currentbuffer));
            _currentbuffer = std::move(buffer1);
            buffers.swap(_buffers);

            if(!_nextbuffer)
                _nextbuffer = std::move(buffer2);
        }

        for(const auto& buffer : buffers)
            _file->append(buffer->data(),buffer->length());
        
        if(!buffer1){
            buffer1 = std::move(buffers.back());
            buffers.pop_back();
            buffer1->reset();
        }

        if(!buffer2){
            buffer2 = std::move(buffers.back());
            buffers.pop_back();
            buffer2->reset();
        }

        buffers.clear();
        _file->flush();
    }

    _file->flush();

    pthread_exit((void*)0);
}

void AsynLog::start(){
    _running = true;
    _thread.start();
    _latch.wait();
}

void AsynLog::stop(){
    // don't use threadmutex, deadlock
    _running = false;
    _condition->notify();
    _thread.join();
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
        _condition->notify();
    }
}

void AsynLog::flush(){
    _file->flush();
}