#include "stdafx.h"
#include "TcpSocket.h"
#include "Log.h"
#include "InnetAddr.h"

using namespace KETTLE;


KETTLE::TcpSocket::TcpSocket(int32 socket)
:_socket(socket){
}

TcpSocket::~TcpSocket(){
	::close(_socket);
}

void TcpSocket::setKeepalive(bool bKeepalive){
	int32 nKeepalive = bKeepalive ? 1:0;
	if(::setsockopt(_socket,SOL_SOCKET,SO_KEEPALIVE,
	&bKeepalive,sizeof(nKeepalive)) != 0)
		LOG_FATA << "setKeepalive error,reason = " << strerror(errno);
}

void TcpSocket::setNodelay(bool bNodelay){
	int32 nNodelay = bNodelay ? 1 : 0;
	if(::setsockopt(_socket,IPPROTO_TCP,TCP_NODELAY,
	&nNodelay,sizeof(nNodelay)) != 0)
		LOG_FATA << "setNodelay error,reason = " << strerror(errno);
}

void TcpSocket::setReuseAddress(bool bReuseAddress){
	int32 nReuseAddress = bReuseAddress ? 1 : 0;
	if(::setsockopt(_socket,SOL_SOCKET,SO_REUSEPORT,
	&nReuseAddress,sizeof(nReuseAddress)) < 0)
		LOG_FATA << "set socket reusepo TCP_NODESO_REUSEPORT error,reason=" 
		<< strerror(errno);
}

void TcpSocket::setNonblock(bool bNonblock){
	if(::ioctl(_socket,FIONBIO,&bNonblock) != 0)
		LOG_FATA << "set socket nonblock error" << ::strerror(errno);
}

void TcpSocket::bindAddress(const InnetAddr& address){
	if(::bind(_socket,(sockaddr*)address.getAddr(),
	sizeof(sockaddr_in)) != 0)
		LOG_FATA << "bind socket error,reason:" << strerror(errno);
}

int32 TcpSocket::accpet(InnetAddr& address){
	socklen_t nSize = sizeof(sockaddr_in);
	int32 socketfd = ::accept(_socket,(sockaddr*)&address._addr,&nSize);
	if(socketfd == -1)
		LOG_ERROR << "accept error,reason=" << strerror(errno);

	return socketfd;
}

void TcpSocket::shutdown(){
	if(::shutdown(_socket,SHUT_WR) != 0)
		LOG_ERROR << "shut down socket error,reason = " << strerror(errno);
}

void TcpSocket::listen(){
	if(::listen(_socket,SOMAXCONN) != 0)
		LOG_ERROR << "listen socket error,reason = " << strerror(errno);
}