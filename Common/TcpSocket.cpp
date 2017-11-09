#include "stdafx.h"
#include "TcpSocket.h"

using namespace KETTLE;

KETTLE::int32 TcpSocket::GetSocket()
{
	return m_Socket;
}

bool KETTLE::TcpSocket::SetBlockMode()
{
#if __WINDOWS__
	u_long iMode = 0;
	if (ioctlsocket(m_Socket, FIONBIO, &iMode) < 0)
	{
		return false;
	}
#elif __LINUX__
#endif
	return true;
}

bool TcpSocket::SetKeepAlive()
{

	return true;
}