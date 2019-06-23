#ifndef __INNET_ADDR_H__
#define __INNET_ADDR_H__

#include "KETTLEPlatform.h"

namespace KETTLE{
    using namespace KETTLE;
    class InnetAddr{
        friend class TcpSocket;
    public:
        InnetAddr(const char* ip,uint16 port);
        InnetAddr(const sockaddr_in& address);
        InnetAddr(const InnetAddr& addr);
        InnetAddr();
        ~InnetAddr(){}

        const uint16    getPort() const {return _port;}
        const sockaddr_in*             getAddr() const;
        const char* getIP();

        InnetAddr& operator=(const sockaddr_in& address);
        const struct sockaddr_in* getSockaddrin(){return &_addr;}
        uint16 getPort(){return _addr.sin_port;}
    private:
        struct sockaddr_in    _addr;
        uint16        _port;
    };
}
#endif