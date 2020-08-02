#include"stdafx.h"
#include"TcpConnection.h"
#include "InnetAddr.h"
#include "EventLoop.h"

TcpConnection::TcpConnection(EventLoop* loop,int32 socket,const InnetAddr& localAddr,
const InnetAddr& remoteAddr):_loop(loop),_socket(new TcpSocket(socket)),
_localAddress(new InnetAddr(localAddr)),
_remoteAddress(new InnetAddr(remoteAddr)),
_channel(new Channel(loop,socket,std::bind(&TcpConnection::handlRead,this)
                    ,std::bind(&TcpConnection::handlWrite,this)
                    ,std::bind(&TcpConnection::handError,this))){

}

TcpConnection::~TcpConnection(){

}

void TcpConnection::handlRead(){
    static const int32 ANOTHER_SIZE = 64 *1024;
    char anotherBuffer[ANOTHER_SIZE] = {0};
    ::iovec iov[2];

    uint32 spaceSize = _readBuffer->writeIndexToEnd();
    iov[0].iov_base = _readBuffer->peek();
    iov[0].iov_len = spaceSize;
    iov[1].iov_base = anotherBuffer;
    iov[1].iov_len = ANOTHER_SIZE;

    ssize_t read_size = ::readv(_socket->GetSocket(),&iov[0],2);
    if(read_size < 0)
        handError();
    else if(read_size <= spaceSize)
        _readBuffer->writeData(read_size);
    else{
        uint32 nAotherSize = read_size - spaceSize;
        _readBuffer->writeData(spaceSize);
        _readBuffer->append(static_cast<char*>(iov[1].iov_base),nAotherSize);
    }
}

void TcpConnection::handlWrite(){
    // if use LT mode ,and writebuff is empty ,need remove epollwriteevent

    if(_writeBuffer->dataSize() == 0){
    }
    else
        ssize_t nWriteSize = ::send(_socket->GetSocket(),_writeBuffer->data(),_writeBuffer->dataSize(),0);
        if(nWriteSize > 0)
            _writeBuffer->readData(nWriteSize);
        else{
            handError();
        }
    }

}

void TcpConnection::handError(){
    _socket->shutdown();
    _loop->removeChannel(_channel.get());
}

void TcpConnection::WriteData(const char* buffer,size_t nSize){
    // need lock?
    _writeBuffer->append(buffer,nSize);

}
void TcpConnection::connectDestroy(){

}