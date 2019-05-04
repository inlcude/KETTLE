#include"Acceptor.h"
#include"Log.h"

KETTLE::Acceptor::Acceptor(const char* ip,const KETTLE::uint16 port){
    _listenSocket.reset(new TcpSocket(true));
    _addr.reset(new InnetAddr(ip,port));
    channel = std::make_shared<KETTLE::Channel>(std::bind(&Acceptor::read,this)
    ,std::bind(&Acceptor::write,this)
    ,std::bind(&Acceptor::error,this));

    if(::bind(_listenSocket->GetSocket(),(const sockaddr*)(_addr->getAddr()),sizeof(struct sockaddr_in)) != 0)
        err_sys("bind error!,%s",strerror(errno));

    if(::listen(_listenSocket->GetSocket(),5) != 0)
        err_sys("listen error!,%s",strerror(errno));
}

void KETTLE::Acceptor::read(){

}

void KETTLE::Acceptor::write(){

}

void KETTLE::Acceptor::error(){

}