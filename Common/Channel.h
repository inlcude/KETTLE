#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class EpollPoller;
    class EventLoop;
    class Channel{

    public:
        typedef std::function<void()>        EventCallback;
        Channel(EventLoop* loop,int32 sockfd,EventCallback read_event
        ,EventCallback write_event
        ,EventCallback error_event);


        ~Channel();

        void handleEvent(int event);
        int32 getSockfd() const{return _sockfd;}
        int32 getEvents() const {return _events;}

     private:
        EventLoop*          _loop;
        int32               _events;
        int32               _sockfd;
        EventCallback       _read;
        EventCallback       _write;
        EventCallback       _error;
    };
}

#endif