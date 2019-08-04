#include"TcpServer.h"
#include"EventLoop.h"
#include"Log.h"

TcpServer::TcpServer(const char* ip,uint16 port,int32 threadNum)
:_eventLoop(new EventLoop()) 
,_acceptor(new Acceptor(_eventPool.get()
                        ,*(_address.get())
                        ,std::bind(&TcpServer::handlAccept
                                    ,this
                                    ,std::placeholders::_1
                                    ,std::placeholders::_2)))
,_running(false)
,_address(new InnetAddr(ip,port))
,_eventPool(new ThreadEventPool(threadNum)){
}

void TcpServer::loop(){
    while(_running){
        // dothing;
        _eventLoop->loop();
    }
}

void TcpServer::start(){
    _running = true;
    _eventPool->start();
    loop();
}

void TcpServer::handlAccept(int32 sockfd,const InnetAddr& address){
    
    TcpConnectionPtr connection = std::make_shared<TcpConnection>(_eventLoop.get(),sockfd,*(_address.get()),address);
    if(_connectionHashMap.find(sockfd) != _connectionHashMap.end())
        _connectionHashMap[sockfd] = connection;
    else
        _connectionHashMap.insert(std::make_pair(sockfd,connection));

    EventLoop* pEventLoop = _eventPool->getNextLoop();
    pEventLoop->runInLoop(connection->getChannel());

    LOG_TRACE << "remote address connected,ip:" << connection->getRemoteAddress().getIP()
    << " port:" << connection->getRemoteAddress().getPort();
    
}