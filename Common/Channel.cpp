#include"Channel.h"
#include "EventLoop.h"


KETTLE::Channel::Channel(EventLoop* loop,int32 sockfd
        ,EventCallback read_event
        ,EventCallback write_event
        ,EventCallback error_event):
        _loop(loop)
        ,_sockfd(sockfd)
        ,_read(read_event)
        ,_write(write_event)
        ,_error(error_event){
        }

KETTLE::Channel::~Channel(){}

void KETTLE::Channel::handleEvent(int event){

    if(event & EPOLLIN | EPOLLPRI | EPOLLHUP)
        _read();
    if(event & EPOLLOUT)
        _write();
    if(event & EPOLLERR)
        _error();
}

void KETTLE::Channel::setEvens(int events)
{
    _events = events;
    _loop->updateChannel(this);
}
