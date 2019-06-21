#ifndef __INNET_ADDR_H__
#define __INNET_ADDR_H__

#include "KETTLEPlatform.h"

namespace KETTLE{
    using namespace KETTLE;
    class InnetAddr{
    public:
        InnetAddr(const char* ip,uint16 port);
        ~InnetAddr(){}

        const uint16    getPort() const{
            return _port;
        } 

        const sockaddr_in*             getAddr() const;
    private:
        struct sockaddr_in    _addr;
        uint16        _port;
    };
}
#endif