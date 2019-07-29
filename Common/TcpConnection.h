#ifndef __TCP_CONNECTION_H
#define __TCP_CONNECTION_H
#include "KETTLEPlatform.h"
#include "TcpSocket.h"
#include "TcpBuffer.h"
#include "Channel.h"

using namespace KETTLE;
namespace KETTLE{
    class InnetAddr;
    class TcpConnection{
        public:
            TcpConnection(EventLoop* loop,int32 socket,const InnetAddr& localAddr,
            const InnetAddr& remoteAddr);
            ~TcpConnection();

            Channel* getChannel() const {return _channel.get();}
            const InnetAddr& getRemoteAddress() const {return *(_remoteAddress.get());}

            void WriteData(const char* buffer,size_t nSize);
        protected:
            void handlRead();
            void handlWrite();
            void handError();
        private:
            EventLoop*                      _loop;
            std::unique_ptr<TcpSocket>      _socket;
            std::unique_ptr<InnetAddr>      _localAddress;      // 我的地址
            std::unique_ptr<InnetAddr>      _remoteAddress;     // 对端地址
            std::unique_ptr<TcpBuffer>      _writeBuffer;
            std::unique_ptr<TcpBuffer>      _readBuffer;
            std::unique_ptr<Channel>        _channel;

    };
}
#endif