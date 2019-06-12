#include "stdafx.h"
#include "ThreadCondition.h"
#include "Log.h"

ThreadCondition::ThreadCondition(ThreadMutex& mutex):_mutex(mutex){
    _condition = PTHREAD_COND_INITIALIZER;
}

ThreadCondition::~ThreadCondition(){

}

void ThreadCondition::wait(){
    if(pthread_cond_wait(&_condition,&_mutex.mutex) != 0)
        LOG_FATA << "pthread_cond_wait error,because: " << strerror(errno);
}

bool ThreadCondition::waitForSecond(int32 second){
    timespec time_spec;
    time_spec.tv_sec = second;
    int result = pthread_cond_timedwait(&_condition,&_mutex.mutex,&time_spec);
    if(result != 0){
        if(result != ETIMEDOUT)
            LOG_FATA << "waitForSecond error,because: " << strerror(errno);
        return false;
    }

    return true;
}

void ThreadCondition::notify(){
    if(pthread_cond_signal(&_condition) != 0)
        LOG_FATA << "condition signal error,because: " << strerror(errno);
}

void ThreadCondition::notifyAll(){
    if(pthread_cond_broadcast(&_condition) !=0 )
        LOG_FATA << "condition broadcast error,because: " << strerror(errno);
}