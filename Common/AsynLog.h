#ifndef __ASYN_LOG_H__
#define __ASYN_LOG_H__

#include "KETTLEPlatform.h"
#include "Thread.h"

using namespace KETTLE;
namespace KETTLE{

    class LargeLoggerStream;
    class AsynLog{
    public:
        AsynLog();
        ~AsynLog();

        void start();
        void stop();

    protected:
        void thread_func();
    private:
        Thread          _thread;
        std::unique_ptr<LargeLoggerStream>      buffer;
        bool                                    _running;
        ThreadMutex                              _mutex;
        std::unique_ptr<ThreadCondition>        _condition;
        CountDownLatch                          _latch;
    };
    
} // namespace KETTLE

#endif