#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class Thread;
    class ThreadPool{
        typedef std::function<void()> ThreadFunc;
        typedef std::shared_ptr<Thread> ThreadPtr;
    public:
        ThreadPool(int32 poolSize);
        ~ThreadPool();

        void start();
        void stop();

    protected:
        void thread_func();
    private:
        const int32                         _threadNum;
        std::list<ThreadPtr>                _threadPool;
        ThreadMutex                         _mutex;
        std::shared_ptr<ThreadCondition>    _condition;

    };
}
#endif