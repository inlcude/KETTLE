#ifndef __INNET_ADDR_H__
#define __INNET_ADDR_H__

#include "KETTLEPlatform.h"

namespace KETTLE{
    class InnetAddr{
    public:
        InnetAddr(const char* ip,KETTLE::uint16 port);
        ~InnetAddr(){}

        const KETTLE::uint16    getPort() const{
            return _port;
        } 

        const sockaddr_in*             getAddr() const;
    private:
        struct sockaddr_in    _addr;
        KETTLE::uint16        _port;
    };
}
#endif