#include "stdafx.h"
#include "CountDownLatch.h"
#include "ThreadCondition.h"
#include "ThreadMutex.h"


CountDownLatch::CountDownLatch(int32 count):
countDown(count),
_mutex()
,_condition(new ThreadCondition(_mutex)){
}

void CountDownLatch::wait(){
    AutoLock autolock(&_mutex);

    while(countDown > 0)
        _condition->wait();
}

void CountDownLatch::countdown(){
    AutoLock autolock(&_mutex);
    countDown--;

    if(countDown == 0)
        _condition->notifyAll();
}