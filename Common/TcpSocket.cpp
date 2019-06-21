#include "stdafx.h"
#include "TcpSocket.h"
#include "Log.h"

using namespace KETTLE;


KETTLE::TcpSocket::TcpSocket(bool block_mode)
:_block(block_mode){
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == -1)
		LOG_FATA << "create socket failed，reason=" << strerror(errno);
	
	int reuse = 1;
	if(::setsockopt(_socket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)) < 0)
		LOG_FATA << "set socket reuseadder error,reason=" << strerror(errno);

	if(::setsockopt(_socket,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(reuse)) < 0)
		LOG_FATA << "set socket reuseport error,reason=" << strerror(errno);
		
	if(block_mode){
		int flags = ::fcntl(_socket, F_GETFL, 0);
		flags |= O_NONBLOCK;
		if(::fcntl(_socket, F_SETFL, flags) < 0)
			LOG_FATA << "set non block error,reason=" << strerror(errno);

		flags = ::fcntl(_socket, F_GETFD, 0);
		flags |= FD_CLOEXEC;
		if(::fcntl(_socket, F_SETFD, flags) < 0)
			LOG_FATA << "set socket cloexec error,reason=" << strerror(errno);
	}
}

TcpSocket::~TcpSocket(){
	::close(_socket);
}

void TcpSocket::setKeepalive(bool bKeepalive){
	int32 nKeepalive = bKeepalive ? 1:0;
	if(::setsockopt(_socket,SOL_SOCKET,SO_KEEPALIVE,&bKeepalive,sizeof(nKeepalive)) != 0)
		LOG_FATA << "setKeepalive error,reason = " << strerror(errno);
}

void TcpSocket::setNodelay(bool bNodelay){
	int32 nNodelay = bNodelay ? 1 : 0;
	if(::setsockopt(_socket,IPPROTO_TCP,TCP_NODELAY,&nNodelay,sizeof(nNodelay)) != 0)
		LOG_FATA << "setNodelay error,reason = " << strerror(errno);
}