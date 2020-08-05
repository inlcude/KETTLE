#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "KETTLEPlatform.h"

#include"Acceptor.h"
#include"Thread.h"
#include"TcpConnection.h"
#include"EventLoop.h"
#include"ThreadEventPool.h"
#include "AsynLog.h"

using namespace KETTLE;
namespace KETTLE{
    class TcpServer{
    public:
        typedef std::shared_ptr<TcpConnection>  TcpConnectionPtr;
        typedef std::unordered_map<int32,TcpConnectionPtr>  ConnectionHashMap;
        typedef std::unordered_map<int32,TcpConnectionPtr>::const_iterator CTC_ITER;
        typedef std::unordered_map<int32,TcpConnectionPtr>::iterator        TC_ITER;
        typedef std::function<void(TcpConnectionPtr ptr,std::string& message)> EventCallback;
    public:
        TcpServer(const char* ip,uint16 port,int32 threadNum,
        EventCallback read_cb,EventCallback write_cb,EventCallback error_cb);
        ~TcpServer();

        void start();
        void exit();

    protected:
        void handlAccept(int32 sockfd,const InnetAddr& address);
        void handleRemoveConnection(TcpConnectionPtr connection);
        void loop();

        static void OutPut(const char* log,int len);
        static void Flush();
    private:
        static TcpServer*               _this;
        std::unique_ptr<AsynLog>        _asynLog;
        bool                            _running;
        // main pool
        std::shared_ptr<EventLoop>      _eventLoop;
        std::unique_ptr<InnetAddr>      _address;
        std::unique_ptr<Acceptor>       _acceptor;
        ConnectionHashMap               _connectionHashMap;
        // mt event pool
        std::unique_ptr<ThreadEventPool> _eventPool;
        EventCallback                   _read_cb;
        EventCallback                   _write_cb;
        EventCallback                   _error_cb;
    };
}
#endif