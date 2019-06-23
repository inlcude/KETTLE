#include"TcpServer.h"

TcpServer::TcpServer(const char* ip,uint16 port)
: _acceptor(new Acceptor(InnetAddr(ip,port),std::bind(&TcpServer::handlAccept,this,std::placeholders::_1,std::placeholders::_2))),_running(false)
,_address(new InnetAddr(ip,port)){
}

void TcpServer::mainLoop(){
    while(_running){
        // dothing;
    }
}

void TcpServer::subLoop(){

}

void TcpServer::start(){

}

void TcpServer::handlAccept(int32 sockfd,const InnetAddr& address){
    
    TcpConnectionPtr connection = std::make_shared<TcpConnection>(sockfd,_address.get(),address);
    if(_connectionHashMap.find(sockfd) != _connectionHashMap.end())
        _connectionHashMap[sockfd] = connection;
    else
        _connectionHashMap.insert(std::make_pair(sockfd,connection));
    
}