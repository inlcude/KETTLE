#include"InnetAddr.h"
#include"Log.h"

KETTLE::InnetAddr::InnetAddr(const char* ip,KETTLE::uint16 port){
    _port = port;
    _addr.sin_port = _port;
    _addr.sin_family = AF_INET;
    if(inet_pton(AF_INET,ip,&(_addr.sin_addr)) <= 0)
        err_sys("inet_pton error,ip:%s",ip);
}

const sockaddr_in* KETTLE::InnetAddr::getAddr() const{
    return &_addr;
}