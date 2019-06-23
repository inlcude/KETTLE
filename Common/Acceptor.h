#ifndef __Acceptor_H__
#define __Acceptor_H__
#include "KETTLEPlatform.h"

#include"TcpSocket.h"
#include"Channel.h"
#include"InnetAddr.h"

using namespace KETTLE;
namespace KETTLE{

	class Acceptor{
		typedef std::function<void(int32,const InnetAddr& address)> HandleConnection;
	public:
		Acceptor(const InnetAddr& address,HandleConnection connection);
		~Acceptor() {}

		void read();
		void write();
		void error();
	private:
		std::unique_ptr<TcpSocket>     _listenSocket;
		std::unique_ptr<InnetAddr> 	   _addr;
		std::shared_ptr<Channel> 		channel;
		HandleConnection			   _connection;
	};
}

#endif