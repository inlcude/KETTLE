#include"InnetAddr.h"
#include"Log.h"

InnetAddr::InnetAddr(const char* ip,uint16 port){
    _port = port;
    _addr.sin_port = htons(port);
    _addr.sin_family = AF_INET;
    if(inet_pton(AF_INET,ip,&(_addr.sin_addr)) <= 0)
        err_sys("inet_pton error,ip:%s",ip);
}

InnetAddr::InnetAddr(const sockaddr_in& address){
    _addr = address;
    _port = _addr.sin_port;
}

InnetAddr::InnetAddr(const InnetAddr& addr){
    _addr = addr._addr;
    _port = addr._port;
}

InnetAddr::InnetAddr():_port(0){
    memset(&_addr,0,sizeof(_addr));
}
const sockaddr_in* InnetAddr::getAddr() const{
    return &_addr;
}

InnetAddr& InnetAddr::operator=(const sockaddr_in& address){
    _addr = address;
    _port = address.sin_port;
    return *this;
}

const char* InnetAddr::getIP(){
    return inet_ntoa(_addr.sin_addr);
}