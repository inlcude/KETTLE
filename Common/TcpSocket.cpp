#include "stdafx.h"
#include "TcpSocket.h"

using namespace KETTLE;
TcpSocket::TcpSocket()
{
	m_Socket = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP);
	if (m_Socket == -1)
		// print some thing
		;
}


TcpSocket::~TcpSocket()
{
}

KETTLE::int32 TcpSocket::GetSocket()
{
	return m_Socket;
}

void TcpSocket::SetBlockMode()
{
#if __WINDOWS__
	u_long iMode = 0;
	if (ioctlsocket(m_Socket, FIONBIO, &iMode) < 0)
		;//do some thing
#elif __LINUX__
#endif
}