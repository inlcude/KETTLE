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

            typedef void (*OutPutFunc)(const char* log,int len);
            typedef void (*FlushFunc)();
        public:
            Logger(LogLevel level,OutPutFunc output_func = &Logger::DefaultWrite,FlushFunc flush_func = &Logger::DefaultFlush);
            ~Logger();

            DefaultLoggerStream&   Stream(){return stream;}
            
            static void DefaultWrite(const char* log,int len);
            static void DefaultFlush();

        private:
            LogLevel                            logLevel;
            DefaultLoggerStream                 stream;
            OutPutFunc                          outfunc;
            FlushFunc                           flushfunc;

    };
}

#endif