#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__
#include "Platform.h"
namespace KETTLE
{
	class TcpSocket
	{
	public:
		TcpSocket();
		~TcpSocket();

		KETTLE::int32                    GetSocket();
		void                             SetBlockMode();
	private:
		KETTLE::int32                    m_Socket;
	};
}

#endif
