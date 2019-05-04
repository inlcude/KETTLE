#include"TcpServer.h"

KETTLE::TcpServer::TcpServer(const char* ip,KETTLE::uint16 port)
: _running(true){
    _acceptor.reset(new Acceptor(ip,port));

    _subReactor.reset(new Thread(std::bind(&TcpServer::subLoop,this)));
}

void KETTLE::TcpServer::mainLoop(){
    while(_running){
        // dothing;
    }
}

void KETTLE::TcpServer::subLoop(){

}

void KETTLE::TcpServer::start(){

}
