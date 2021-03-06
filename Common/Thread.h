#ifndef __THREAD_H__
#define __THREAD_H__

#include<list>

#include"KETTLEPlatform.h"
#include"ThreadMutex.h"
#include "CountDownLatch.h"

using namespace KETTLE;
namespace KETTLE{
	class Thread{
        public:
            typedef std::function<void()> ThreadFunc;

            Thread(ThreadFunc func);
            ~Thread();

            void start();
            void stop();
            void loop();
            void join();

    
        private:
            CountDownLatch  _countDown;
            ThreadFunc      _func;
            pthread_t       _tid;
            bool            _running;
    };
}
#endif