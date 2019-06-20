#ifndef __LOG_FILE_H__
#define __LOG_FILE_H__

#include"KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{

    class LoggerFile{
        public:
            LoggerFile();
            void flush();
            void append(const char* log,uint32 len);
        protected:
            void rollFile();
            void checkrollFile();
        private:
            FILE*                               file;
            int64                               writesize;
            const static int32                  MAX_LOGFILE_SIZE = 500*1024*1024;
    };
}

#endif