#ifndef _COUNTEDOWN_LATCH_H_
#define _COUNTEDOWN_LATCH_H_
#include"KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class ThreadCondition;
    class CountDownLatch{
        public:
            CountDownLatch(int32 count);
            ~CountDownLatch();

            void wait();
            void countdown();
        private:
            int32                                   countDown;
            ThreadMutex                             _mutex;
            std::unique_ptr<ThreadCondition>        _condition;
    };
}
#endif