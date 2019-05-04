#include "stdafx.h"
#include "TcpSocket.h"

using namespace KETTLE;


KETTLE::TcpSocket::TcpSocket(){
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == -1) 
		std::cout << "error";
				// print some thing
}

KETTLE::int32 TcpSocket::GetSocket() const{
	return m_Socket;
}

bool KETTLE::TcpSocket::SetBlockMode(){
	return true;
}

bool TcpSocket::SetKeepAlive(){
	
	return true;
}