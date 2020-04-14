#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__
#include "KETTLEPlatform.h"


namespace KETTLE{
	
	using namespace KETTLE;
	class InnetAddr;
	class TcpSocket{
	public:
		TcpSocket(int32 socket);
		~TcpSocket();


		const KETTLE::int32 GetSocket() const{return _socket;}
		void setKeepalive(bool bKeepalive);
		void setNodelay(bool bNodelay);
		void setReuseAddress(bool bReuseAddress);
		void bindAddress(const InnetAddr& address);
		void listen();
		void setNonblock(bool bNonblock);
		int32 accpet(InnetAddr& address);
		void shutdown();
		
	private:
		int32                    _socket;
	};
}

#endif
