#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__
#include "KETTLEPlatform.h"
namespace KETTLE
{
	class TcpSocket
	{
	public:
		TcpSocket(void)
		{
			m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (m_Socket == -1)
				// print some thing
			    ;

		}
		~TcpSocket() {}

		KETTLE::int32                    GetSocket();
		bool                             SetBlockMode();
		bool                             SetKeepAlive();
	private:
		KETTLE::int32                    m_Socket;
	};
}

#endif
