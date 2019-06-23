#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "KETTLEPlatform.h"

using namespace KETTLE;
namespace KETTLE{
    class Channel{
    public:
        typedef std::function<void()>        EventCallback;
        Channel(int32 sockfd,EventCallback read_event
        ,EventCallback write_event
        ,EventCallback error_event);


        ~Channel();

        void handleEvent(int event);
        int32 getSockfd(){return _sockfd;}

     private:
        int32               _sockfd;
        EventCallback       _read;
        EventCallback       _write;
        EventCallback       _error;
    };
}

#endif