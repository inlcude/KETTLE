#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "KETTLEPlatform.h"

#include"Acceptor.h"
#include"Thread.h"
#include"TcpConnection.h"
#include"EventLoop.h"
#include"ThreadEventPool.h"

using namespace KETTLE;
namespace KETTLE{
    class TcpServer{
        typedef std::shared_ptr<TcpConnection>  TcpConnectionPtr;
        typedef std::unordered_map<int32,TcpConnectionPtr>  ConnectionHashMap;
        typedef std::unordered_map<int32,TcpConnectionPtr>::const_iterator CTC_ITER;
        typedef std::unordered_map<int32,TcpConnectionPtr>::iterator        TC_ITER;
    public:
        TcpServer(const char* ip,uint16 port,int32 threadNum);
        ~TcpServer();

        void start();
        void exit();

    protected:
        void handlAccept(int32 sockfd,const InnetAddr& address);
        void loop();
    private:
        bool                            _running;
        // main pool
        std::shared_ptr<EventLoop>      _eventLoop;
        std::unique_ptr<InnetAddr>      _address;
        std::unique_ptr<Acceptor>       _acceptor;
        ConnectionHashMap               _connectionHashMap;
        // mt event pool
        std::unique_ptr<ThreadEventPool> _eventPool;
    };
}
#endif