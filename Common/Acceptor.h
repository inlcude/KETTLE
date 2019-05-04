#ifndef __Acceptor_H__
#define __Acceptor_H__
#include "KETTLEPlatform.h"

#include"TcpSocket.h"
namespace KETTLE{

	class Acceptor{
	public:
		Acceptor();
		~Acceptor() {}
	private:
		std::shared_ptr<KETTLE::TcpSocket>     _listenSocket;     
	};
}

#endif