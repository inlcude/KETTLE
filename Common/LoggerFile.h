#ifndef __LOG_FILE_H__
#define __LOG_FILE_H__

#include"KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class LoggerStream;

    class LoggerFile{
        public:
            LoggerFile();
            void flush();
            void append(const char* log,uint32 len);
        private:
            FILE*                               file;
            int64                               writesize;
    };
}

#endif