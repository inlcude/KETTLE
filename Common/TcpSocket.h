#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__
#include "KETTLEPlatform.h"


namespace KETTLE{
	
	class TcpSocket{
	public:
		TcpSocket(bool block_mode);
		~TcpSocket() {}

		const KETTLE::int32                    GetSocket() const;
		bool                             	   SetKeepAlive();
	private:
		KETTLE::int32                    _socket;
		bool							 _block;
	};
}

#endif
