#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__
#include "KETTLEPlatform.h"
<<<<<<< HEAD
namespace KETTLE{

	class TcpSocket{
	public:
		TcpSocket(){
			m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (m_Socket == -1) 
				std::cout << "error";
		}
=======


namespace KETTLE{
	
	class TcpSocket{
	public:
		TcpSocket(bool block_mode);
>>>>>>> 8a763a70ec399ef8c706e49c961352ed03a9a5f6
		~TcpSocket() {}

		const KETTLE::int32                    GetSocket() const;
		bool                             	   SetKeepAlive();
	private:
<<<<<<< HEAD
		KETTLE::int32                    m_Socket;
		sockaddr_in					     address;
=======
		KETTLE::int32                    _socket;
		bool							 _block;
>>>>>>> 8a763a70ec399ef8c706e49c961352ed03a9a5f6
	};
}

#endif
