#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "KETTLEPlatform.h"

#include"Acceptor.h"
#include"Thread.h"
#include"TcpConnection.h"
#include"EventLoop.h"

using namespace KETTLE;
namespace KETTLE{
    class TcpServer{
        typedef std::shared_ptr<TcpConnection>  TcpConnectionPtr;
        typedef std::unordered_map<int32,TcpConnectionPtr>  ConnectionHashMap;
        typedef std::unordered_map<int32,TcpConnectionPtr>::const_iterator CTC_ITER;
        typedef std::unordered_map<int32,TcpConnectionPtr>::iterator        TC_ITER;
    public:
        TcpServer(const char* ip,uint16 port);
        ~TcpServer();

        void start();

        void mainLoop();
        void subLoop();
    protected:
        void handlAccept(int32 sockfd,const InnetAddr& address);
    private:
        std::unique_ptr<Acceptor>       _acceptor;
        bool                            _running;
        std::unique_ptr<InnetAddr>      _address;
        ConnectionHashMap               _connectionHashMap;
        std::shared_ptr<EventLoop>      _eventLoop;
    };
}
#endif