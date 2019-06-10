#ifndef __Acceptor_H__
#define __Acceptor_H__
#include "KETTLEPlatform.h"

#include"TcpSocket.h"
#include"Channel.h"
#include"InnetAddr.h"

namespace KETTLE{

	class Acceptor{
	public:
		Acceptor(const char* ip,const KETTLE::uint16 port);
		~Acceptor() {}

		void read();
		void write();
		void error();
	private:
		std::unique_ptr<KETTLE::TcpSocket>     _listenSocket;
		std::unique_ptr<KETTLE::InnetAddr> 		_addr;
		std::shared_ptr<KETTLE::Channel> 		channel;
	};
}

#endif