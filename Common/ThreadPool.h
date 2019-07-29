#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class Thread;
    class ThreadPool{
        typedef std::function<void()> ThreadFunc;
        typedef std::shared_ptr<Thread> ThreadPtr;
        typedef std::function<void()>   Task;
    public:
        ThreadPool(int32 poolSize);
        ~ThreadPool();

        void start();
        void stop();
        void runInThread(Task task);

        uint32 getTaskNums(){return _taskDeque.size();}

    protected:
        Task take();
        void thread_func();
    private:
        const int32                         _threadNum;
        std::list<ThreadPtr>                _threadPool;
        ThreadMutex                         _mutex;
        std::shared_ptr<ThreadCondition>    _condition;
        bool                                _running;
        std::deque<Task>                    _taskDeque;

    };
}
#endif