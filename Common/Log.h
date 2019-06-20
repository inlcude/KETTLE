#ifndef __LOG_H__
#define __LOG_H__

#include"KETTLEPlatform.h"
#include"ThreadMutex.h"
#include"LoggerStream.h"

void err_msg(const char*,...);
void err_dump(const char*,...) __attribute__((noreturn));
void err_quit(const char*,...) __attribute__((noreturn));
void err_cont(int,const char*,...);
void err_exit(int,const char*,...) __attribute__((noreturn));
void err_ret(const char*,...);
void err_sys(const char*,...) __attribute__((noreturn));


using namespace KETTLE;
namespace KETTLE{

#define LOG_INFO  Logger(Logger::KETTLE_LOGGER_LEVEL_INFO).Stream()
#define LOG_TRACE Logger(Logger::KETTLE_LOGGER_LEVEL_TRACE).Stream()
#define LOG_DEBUG Logger(Logger::KETTLE_LOGGER_LEVEL_DEBUG).Stream()
#define LOG_ERROR Logger(Logger::KETTLE_LOGGER_LEVEL_ERROR).Stream()
#define LOG_FATA  Logger(Logger::KETTLE_LOGGER_LEVEL_FATA).Stream()

typedef void (*OutPutFunc)(const char* log,int len);
typedef void (*FlushFunc)();

    class Logger{

        public:
            enum LogLevel{
                KETTLE_LOGGER_LEVEL_INFO,
                KETTLE_LOGGER_LEVEL_TRACE,
                KETTLE_LOGGER_LEVEL_DEBUG,
                KETTLE_LOGGER_LEVEL_ERROR,
                KETTLE_LOGGER_LEVEL_FATA,
                KETTLE_LOGGER_LEVEL_NUMS,
            };
        public:
            Logger(LogLevel level);
            ~Logger();

            DefaultLoggerStream&   Stream(){return stream;}
            
            static void DefaultWrite(const char* log,int len);
            static void DefaultFlush();

            static void setOutPutFunc(OutPutFunc func){outfunc = func;}
            static void setFlushFunc(FlushFunc func){flushfunc = func;}

        private:
            LogLevel                            logLevel;
            DefaultLoggerStream                 stream;
            static OutPutFunc                   outfunc;
            static FlushFunc                    flushfunc;

    };
}

#endif