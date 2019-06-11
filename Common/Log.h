#ifndef __LOG_H__
#define __LOG_H__

#include"KETTLEPlatform.h"
#include"ThreadMutex.h"

void err_msg(const char*,...);
void err_dump(const char*,...) __attribute__((noreturn));
void err_quit(const char*,...) __attribute__((noreturn));
void err_cont(int,const char*,...);
void err_exit(int,const char*,...) __attribute__((noreturn));
void err_ret(const char*,...);
void err_sys(const char*,...) __attribute__((noreturn));


namespace KETTLE{

    class LoggerStream{
        public:
            LoggerStream():curPos(0){
                cleanUp();
            }

            void cleanUp() {memset(logBuffer,0,BUFFSIZE);}
            KETTLE::int32 availd() {return BUFFSIZE - curPos;}
            const char* data() {return logBuffer;}
            KETTLE::int32 length() {return curPos;}

        public:
            LoggerStream& operator<< (KETTLE::int64 log){
                char szBuffer[128] = {0};
                snprintf(szBuffer,128,"%lld",log);
                append(szBuffer);
                return *this;
            }
            LoggerStream& operator<< (KETTLE::int32 log){
                char szBuffer[128] = {0};
                snprintf(szBuffer,128,"%d",log);
                append(szBuffer);
                return *this;
            }
            LoggerStream& operator<< (KETTLE::int16 log){
                char szBuffer[128] = {0};
                snprintf(szBuffer,128,"%d",log);
                append(szBuffer);
                return *this;
            }
            LoggerStream& operator<< (KETTLE::int8 log){
                char szBuffer[128] = {0};
                snprintf(szBuffer,128,"%d",log);
                append(szBuffer);
                return *this;
            }
            LoggerStream& operator<< (KETTLE::int8* log){
                append(log);
                return *this;
            }

            LoggerStream& operator <<(const KETTLE::int8* log){
                *this << const_cast<KETTLE::int8*>(log);
                return *this;
            }

            LoggerStream& operator<< (KETTLE::double64 log){
                char szBuffer[128] = {0};
                snprintf(szBuffer,128,"%f",log);
                append(szBuffer);
                return *this;
            }
            LoggerStream& operator<< (KETTLE::float32 log){
                char szBuffer[128] = {0};
                snprintf(szBuffer,128,"%f",log);
                append(szBuffer);
                return *this;
            }

        private:
            void addlength(int length){
                curPos += length;
            }
            void append(const char* str){
                int len = strlen(str);
                if(availd() >= len){
                    memcpy(&logBuffer[curPos],str,len);
                    addlength(len);
                }
            }
        private:
            static const KETTLE::int32 BUFFSIZE = 4096;
            char                    logBuffer[BUFFSIZE];
            KETTLE::int32           curPos;

    };
    

    class LoggerFile{
        public:
            LoggerFile();
            void flush(std::shared_ptr<LoggerStream> stream);
        private:
            FILE*                               file;
    };

#define LOG_INFO  Logger(Logger::KETTLE_LOGGER_LEVEL_INFO).Stream()
#define LOG_TRACE Logger(Logger::KETTLE_LOGGER_LEVEL_TRACE).Stream()
#define LOG_DEBUG Logger(Logger::KETTLE_LOGGER_LEVEL_DEBUG).Stream()
#define LOG_ERROR Logger(Logger::KETTLE_LOGGER_LEVEL_ERROR).Stream()
#define LOG_FATA  Logger(Logger::KETTLE_LOGGER_LEVEL_FATA).Stream()

typedef void (*OutPutFunc)(const char* log,int len);
typedef void (*FlushFunc)();
//void DefaultWrite(const char* log,int len);


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
            Logger(LogLevel level,OutPutFunc output_func = &Logger::DefaultWrite,FlushFunc flush_func = &Logger::DefaultFlush);
            ~Logger();

            LoggerStream&   Stream(){return stream;}
            
            static void DefaultWrite(const char* log,int len);
            static void DefaultFlush();

        private:
            LogLevel                            logLevel;
            LoggerStream                        stream;
            OutPutFunc                          outfunc;
            FlushFunc                           flushfunc;

    };
}

#endif