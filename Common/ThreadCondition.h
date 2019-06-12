#ifndef _THREAD_CONDITION_H_
#define _THREAD_CONDITION_H_
#include"KETTLEPlatform.h"

using namespace KETTLE;
namespace  KETTLE{
    class ThreadMutex;
    class ThreadCondition{
    public:
        ThreadCondition(ThreadMutex& mutex);
        ~ThreadCondition();

        bool waitForSecond(int32 second);
        void wait();
        void notify();
        void notifyAll();

    private:
        ThreadMutex&        _mutex;
        pthread_cond_t      _condition;
    };
} // namespace  KETTLE

#endif