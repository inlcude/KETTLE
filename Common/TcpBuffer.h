#ifndef __TCP_BUFFER_H__
#define __TCP_BUFFER_H__
#include"KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class TcpBuffer{
        friend class TcpConnection;
        static const int32 INIT_TCP_BUFFERRR_SIZE = 1024;
        public:
            TcpBuffer(uint32 initSize = INIT_TCP_BUFFERRR_SIZE);

            void append(const char* stream,int32 lenth);
            uint32 writeIndexToEnd(){return _buffer.size() - writeIndex;}
            uint32 space(){return _buffer.size() - writeIndex + readIndex;}
            uint32 dataSize(){return writeIndex - readIndex;}
            void dilatation(int32 writeSize);
            std::string retrieve();
            char* peek(){return &_buffer[writeIndex];}
            char* data(){return &_buffer[readIndex];}
        protected:
            void writeData(uint32 nSize){writeIndex += nSize;}
            void readData(uint32 nSize){readIndex += nSize;}
        private:
            std::vector<char>       _buffer;
            uint32 readIndex;
            uint32 writeIndex;
    };
    
} // namespace KETTLE;

#endif