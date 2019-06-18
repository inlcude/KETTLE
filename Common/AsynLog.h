#ifndef __ASYN_LOG_H__
#define __ASYN_LOG_H__

#include "KETTLEPlatform.h"
#include "Thread.h"
#include"LoggerStream.h"

using namespace KETTLE;
namespace KETTLE{

    class LoggerFile;


    class AsynLog{
        typedef std::unique_ptr<LargeLoggerStream> LogBuffer;
        typedef std::vector<LogBuffer>             LogBuffers;
    public:
        AsynLog();
        ~AsynLog();

        void start();
        void stop();

        void append(const char* log,int32 len);

    protected:
        void thread_func();
    private:
        Thread                                  _thread;
        LogBuffer                               _writebuffer;
        LogBuffer                               _currentbuffer;
        LogBuffer                               _nextbuffer;
        LogBuffers                              _buffers;
        bool                                    _running;
        ThreadMutex                             _mutex;
        std::unique_ptr<ThreadCondition>        _condition;
        CountDownLatch                          _latch;
        std::unique_ptr<LoggerFile>             _file;
    };
    
} // namespace KETTLE

#endif