#include "stdafx.h"
#include "TcpBuffer.h"


TcpBuffer::TcpBuffer(uint32 initSize):_buffer(initSize),
readIndex(0),writeIndex(0){

}

void TcpBuffer::append(const char* stream,int32 lenth){
    if(writeIndexToEnd() < lenth)
        dilatation(lenth);

    std::copy(stream,stream+lenth,&_buffer[writeIndex]);
    writeIndex += lenth;
}

void TcpBuffer::dilatation(int32 writeSize){
    if(space() < writeSize){
        _buffer.resize(writeIndex + writeSize);
    }
    else{
        std::copy(readIndex,writeIndex,peek());
        uint32 write_offset = dataSize();
        readIndex = 0;
        writeIndex = write_offset;
    }
}

std::string TcpBuffer::retrieve(){
    uint32 ndataSize = dataSize();
    std::string data(peek() + readIndex,ndataSize);
    readIndex += ndataSize;
}