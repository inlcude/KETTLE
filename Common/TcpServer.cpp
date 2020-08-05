#include"TcpServer.h"
#include"EventLoop.h"
#include"Log.h"

TcpServer* TcpServer::_this = nullptr;

TcpServer::TcpServer(const char* ip,uint16 port,int32 threadNum,
EventCallback read_cb,EventCallback write_cb,EventCallback error_cb)
:_asynLog(new AsynLog)
,_eventLoop(new EventLoop()) 
,_acceptor(new Acceptor(_eventLoop.get()
                        ,*(_address.get())
                        ,std::bind(&TcpServer::handlAccept
                                    ,this
                                    ,std::placeholders::_1
                                    ,std::placeholders::_2)))
,_running(false)
,_address(new InnetAddr(ip,port))
,_eventPool(new ThreadEventPool(threadNum))
,_read_cb(read_cb)
,_write_cb(write_cb)
,_error_cb(error_cb){
    _this = this;

    KETTLE::Logger::setOutPutFunc(TcpServer::OutPut);
    KETTLE::Logger::setFlushFunc(TcpServer::Flush);

    _asynLog->start();
}

TcpServer::~TcpServer(){

}

void TcpServer::OutPut(const char* log,int len){
    _this->_asynLog->append(log,len);
}

void TcpServer::Flush(){
    _this->_asynLog->flush();
}

void TcpServer::loop(){
    // dothing;
    _eventLoop->startLoop();
}

void TcpServer::exit(){
    _asynLog->stop();
}

void TcpServer::start(){
    LOG_INFO << "Tcp server start,listen on " << _address->getIP() << " listen on port:" << _address->getPort();
    _running = true;
    _eventPool->start();
    loop();
}

void TcpServer::handlAccept(int32 sockfd,const InnetAddr& address){
    
    TcpConnectionPtr connection = std::make_shared<TcpConnection>(_eventLoop.get()
    ,sockfd
    ,*(_address.get())
    ,address
    ,_read_cb
    ,_write_cb
    ,_error_cb);
    if(_connectionHashMap.find(sockfd) != _connectionHashMap.end())
        _connectionHashMap[sockfd] = connection;
    else
        _connectionHashMap.insert(std::make_pair(sockfd,connection));

    EventLoop* pEventLoop = _eventPool->getNextLoop();
    pEventLoop->runInLoop(connection->getChannel());

    LOG_TRACE << "remote address connected,ip:" << connection->getRemoteAddress().getIP()
    << " port:" << connection->getRemoteAddress().getPort();
    
}

void TcpServer::handleRemoveConnection(TcpConnectionPtr connection){
    EventLoop* loop = connection->getLoop();
}