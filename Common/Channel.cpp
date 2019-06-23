#include"Channel.h"


KETTLE::Channel::Channel(int32 sockfd,EventCallback read_event
        ,EventCallback write_event
        ,EventCallback error_event):
        _sockfd(sockfd),
        _read(read_event)
        ,_write(write_event)
        ,_error(write_event){

        }

KETTLE::Channel::~Channel(){}

void KETTLE::Channel::handleEvent(int event){

}