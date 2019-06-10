#include "stdafx.h"
#include "TcpSocket.h"
#include "Log.h"

using namespace KETTLE;


KETTLE::TcpSocket::TcpSocket(bool block_mode)
:_block(block_mode){
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == -1) 
		err_sys("create socket failed,%s",strerror(errno));
	
	int reuse = 1;
	if(::setsockopt(_socket,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)) < 0)
		err_sys("set socket reuseadder error,%s",strerror(errno));

	if(::setsockopt(_socket,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(reuse)) < 0)
		err_sys("set socket reuseport error,%s",strerror(errno));
		
	if(block_mode){
		int flags = ::fcntl(_socket, F_GETFL, 0);
		flags |= O_NONBLOCK;
		if(::fcntl(_socket, F_SETFL, flags) < 0)
			err_sys("set non block error,%s",strerror(errno));

		flags = ::fcntl(_socket, F_GETFD, 0);
		flags |= FD_CLOEXEC;
		if(::fcntl(_socket, F_SETFD, flags) < 0)
			err_sys("set socket cloexec error,%s",strerror(errno));
	}
}

const KETTLE::int32 TcpSocket::GetSocket() const{
	return _socket;
}

bool TcpSocket::SetKeepAlive(){	
	return true;
}