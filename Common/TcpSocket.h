#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__
#include "KETTLEPlatform.h"


namespace KETTLE{
	
	class TcpSocket{
	public:
		TcpSocket();
		~TcpSocket() {}

		KETTLE::int32                    GetSocket() const;
		bool                             SetBlockMode();
		bool                             SetKeepAlive();
	private:
		KETTLE::int32                    m_Socket;
	};
}

#endif
