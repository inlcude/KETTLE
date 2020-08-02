#include"Acceptor.h"
#include"Log.h"
#include "TcpSocket.h"
#include "EventLoop.h"

Acceptor::Acceptor(EventLoop* loop,const InnetAddr& address,HandleConnection connection):
_loop(loop)
,_addr(new InnetAddr(address))
,_connection(connection){

    int32 sockfd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
        LOG_FATA << "socket() error,reason" << strerror(errno);

    _listenSocket.reset(new TcpSocket(sockfd));
    _listenSocket->setReuseAddress(true);

    channel = std::make_shared<Channel>(loop,sockfd,std::bind(&Acceptor::read,this)
    ,std::bind(&Acceptor::write,this)
    ,std::bind(&Acceptor::error,this));

    _listenSocket->bindAddress(*(_addr.get()));
    _listenSocket->listen();
    _loop->runInLoop(channel.get());
}

void Acceptor::read(){
    InnetAddr address;
    int32 sockfd = _listenSocket->accpet(address);
    if(sockfd < 0)
        LOG_ERROR << "accpet error,reason:" << strerror(errno);

    _connection(sockfd,address);
    
}

void Acceptor::write(){

}

void Acceptor::error(){

}

Channel* Acceptor::get_channel(){
    return channel.get();
}