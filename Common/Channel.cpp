#include"Channel.h"


KETTLE::Channel::Channel(EventCallback read_event
        ,EventCallback write_event
        ,EventCallback error_event):
        _read(read_event)
        ,_write(write_event)
        ,_error(write_event){

        }

KETTLE::Channel::~Channel(){}

void KETTLE::Channel::handleEvent(int event){

}