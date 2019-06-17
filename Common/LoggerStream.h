#ifndef __LOG_STREAM_H__
#define __LOG_STREAM_H__
#include"KETTLEPlatform.h"


using namespace KETTLE;
namespace KETTLE{

        template<int32 MAX_SIZE>
        class LoggerStream{
        public:
            LoggerStream():curPos(0){
                cleanUp();
            }

            void cleanUp() {memset(logBuffer,0,BUFFSIZE);}
            KETTLE::int32 availd() {return BUFFSIZE - curPos;}
            const char* data() {return logBuffer;}
            KETTLE::int32 length() {return curPos;}
            void reset(){
                cleanUp();
                curPos = 0;
            }

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
            char                    logBuffer[MAX_SIZE];
            int32                   curPos;
    };

    static const int32 DEFAULT_BUFFER_SIZE = 4096;
    static const int32 LARGE_BUFFER_SIZE = 4096 * 1000;

    typedef LoggerStream<DEFAULT_BUFFER_SIZE> DefaultLoggerStream;
    typedef LoggerStream<LARGE_BUFFER_SIZE> LargeLoggerStream;
} // namespace KETTLE

#endif
