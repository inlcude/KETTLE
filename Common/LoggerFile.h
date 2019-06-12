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
        private:
            FILE*                               file;
    };
}

#endif