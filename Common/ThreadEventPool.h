#ifndef _THREAD_EVENT_POOL_H
#define _THREAD_EVENT_POOL_H
#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class EventLoop;
    class Thread;
    class ThreadEventPool{
        public:
            ThreadEventPool(int32 threadNum);

            EventLoop* getNextLoop();
            void start();

        private:
            std::atomic_int32_t             _nCount;
            std::vector<EventLoop*>         _eventPool;
            std::vector<Thread*>            _threadPool;
            int32                           _threadNum;
    };
}

#endif