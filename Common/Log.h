#ifndef __LOG_H__
#define __LOG_H__

#include"KETTLEPlatform.h"

void err_msg(const char*,...);
void err_dump(const char*,...) __attribute__((noreturn));
void err_quit(const char*,...) __attribute__((noreturn));
void err_cont(int,const char*,...);
void err_exit(int,const char*,...) __attribute__((noreturn));
void err_ret(const char*,...);
void err_sys(const char*,...) __attribute__((noreturn));

namespace KETTLE{

    class LoggerStream{

    };
    class Logger{
        public:
            enum{
                KETTLE_LOGGER_LEVEL_INFO,
                KETTLE_LOGGER_LEVEL_TRACE,
                KETTLE_LOGGER_LEVEL_DEBUG,
                KETTLE_LOGGER_LEVEL_ERROR,
                KETTLE_LOGGER_LEVEL_FATA,
                KETTLE_LOGGER_LEVEL_NUMS,
            };

        private:
            void    AppendLog(KETTLE::int32 log);
            void    AppendLog(KETTLE::int16 log);
            void    AppendLog(KETTLE::int16 log);
            void    AppendLog(KETTLE::int8* log);
            void    AppendLog(KETTLE::double64 log);
            void    AppendLog(KETTLE::float32 log);

        private:
            FILE*           file;
            std::shared_ptr<ThreadMutex>        mutex;

    };
}

#endif